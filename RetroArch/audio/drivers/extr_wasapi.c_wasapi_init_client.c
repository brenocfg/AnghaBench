#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  double UINT32 ;
typedef  unsigned int REFERENCE_TIME ;
typedef  int /*<<< orphan*/  IMMDevice ;
typedef  int /*<<< orphan*/  IAudioClient ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RARCH_LOG (char*,...) ; 
 int /*<<< orphan*/  RARCH_WARN (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _IAudioClient_GetBufferSize (int /*<<< orphan*/ *,double*) ; 
 int /*<<< orphan*/  _IAudioClient_GetDevicePeriod (int /*<<< orphan*/ *,unsigned int*,unsigned int*) ; 
 int /*<<< orphan*/  _IAudioClient_GetStreamLatency (int /*<<< orphan*/ *,unsigned int*) ; 
 int /*<<< orphan*/ * wasapi_init_client_ex (int /*<<< orphan*/ *,int*,unsigned int*,unsigned int) ; 
 int /*<<< orphan*/ * wasapi_init_client_sh (int /*<<< orphan*/ *,int*,unsigned int*,unsigned int) ; 

__attribute__((used)) static IAudioClient *wasapi_init_client(IMMDevice *device, bool *exclusive,
      bool *float_fmt, unsigned *rate, unsigned latency)
{
   HRESULT hr;
   IAudioClient *client;
   double latency_res;
   REFERENCE_TIME device_period  = 0;
   REFERENCE_TIME stream_latency = 0;
   UINT32 buffer_length          = 0;

   if (*exclusive)
   {
      client = wasapi_init_client_ex(device, float_fmt, rate, latency);
      if (!client)
      {
         client = wasapi_init_client_sh(device, float_fmt, rate, latency);
         if (client)
            *exclusive = false;
      }
   }
   else
   {
      client = wasapi_init_client_sh(device, float_fmt, rate, latency);
      if (!client)
      {
         client = wasapi_init_client_ex(device, float_fmt, rate, latency);
         if (client)
            *exclusive = true;
      }
   }

   if (!client)
      return NULL;

   /* next calls are allowed to fail (we losing info only) */

   if (*exclusive)
      hr = _IAudioClient_GetDevicePeriod(client, NULL, &device_period);
   else
      hr = _IAudioClient_GetDevicePeriod(client, &device_period, NULL);

   if (FAILED(hr))
   {
      RARCH_WARN("[WASAPI]: IAudioClient::GetDevicePeriod failed with error 0x%.8X.\n", hr);
   }

   if (!*exclusive)
   {
      hr = _IAudioClient_GetStreamLatency(client, &stream_latency);
      if (FAILED(hr))
      {
         RARCH_WARN("[WASAPI]: IAudioClient::GetStreamLatency failed with error 0x%.8X.\n", hr);
      }
   }

   hr = _IAudioClient_GetBufferSize(client, &buffer_length);
   if (FAILED(hr))
   {
      RARCH_WARN("[WASAPI]: IAudioClient::GetBufferSize failed with error 0x%.8X.\n", hr);
   }

   if (*exclusive)
      latency_res = (double)buffer_length * 1000.0 / (*rate);
   else
      latency_res = (double)(stream_latency + device_period) / 10000.0;

   RARCH_LOG("[WASAPI]: Client initialized (%s, %s, %uHz, %.1fms).\n",
         *exclusive ? "exclusive" : "shared",
         *float_fmt ? "float" : "pcm", *rate, latency_res);

   RARCH_LOG("[WASAPI]: Client's buffer length is %u frames (%.1fms).\n",
         buffer_length, (double)buffer_length * 1000.0 / (*rate));

   RARCH_LOG("[WASAPI]: Device period is %.1fms (%lld frames).\n",
         (double)device_period / 10000.0, device_period * (*rate) / 10000000);

   return client;
}