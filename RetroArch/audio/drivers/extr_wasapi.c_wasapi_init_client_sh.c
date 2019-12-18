#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  WAVEFORMATEXTENSIBLE ;
typedef  int /*<<< orphan*/  WAVEFORMATEX ;
struct TYPE_8__ {scalar_t__ (* Initialize ) (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ;TYPE_1__* lpVtbl; } ;
struct TYPE_7__ {scalar_t__ (* Initialize ) (TYPE_2__*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ;} ;
typedef  int /*<<< orphan*/  IMMDevice ;
typedef  TYPE_2__ IAudioClient ;
typedef  scalar_t__ HRESULT ;

/* Variables and functions */
 scalar_t__ AUDCLNT_E_ALREADY_INITIALIZED ; 
 scalar_t__ AUDCLNT_E_UNSUPPORTED_FORMAT ; 
 int /*<<< orphan*/  AUDCLNT_SHAREMODE_SHARED ; 
 int AUDCLNT_STREAMFLAGS_EVENTCALLBACK ; 
 int AUDCLNT_STREAMFLAGS_NOPERSIST ; 
 int /*<<< orphan*/  CLSCTX_ALL ; 
 scalar_t__ FAILED (scalar_t__) ; 
 int /*<<< orphan*/  IFACE_RELEASE (TYPE_2__*) ; 
 int /*<<< orphan*/  IID_IAudioClient ; 
 int /*<<< orphan*/  RARCH_LOG (char*,char*,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  RARCH_WARN (char*) ; 
 scalar_t__ _IMMDevice_Activate (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,void**) ; 
 scalar_t__ stub1 (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ stub2 (TYPE_2__*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ stub3 (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ stub4 (TYPE_2__*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 unsigned int wasapi_pref_rate (int) ; 
 int /*<<< orphan*/  wasapi_set_format (int /*<<< orphan*/ *,int,unsigned int) ; 

__attribute__((used)) static IAudioClient *wasapi_init_client_sh(IMMDevice *device,
      bool *float_fmt, unsigned *rate, unsigned latency)
{
   WAVEFORMATEXTENSIBLE wf;
   int i, j;
   IAudioClient *client = NULL;
   bool float_fmt_res   = *float_fmt;
   unsigned rate_res    = *rate;
   HRESULT hr           = _IMMDevice_Activate(device,
         IID_IAudioClient,
         CLSCTX_ALL, NULL, (void**)&client);
   if (FAILED(hr))
      return NULL;

   /* once for float, once for pcm (requested first) */
   for (i = 0; i < 2; ++i)
   {
      rate_res = *rate;
      if (i == 1)
         float_fmt_res = !float_fmt_res;

      /* for requested rate (first) and all preferred rates */
      for (j = 0; rate_res; ++j)
      {
         RARCH_LOG("[WASAPI]: Initializing client (shared, %s, %uHz, %ums) ...\n",
               float_fmt_res ? "float" : "pcm", rate_res, latency);

         wasapi_set_format(&wf, float_fmt_res, rate_res);
#ifdef __cplusplus
         hr = client->Initialize(AUDCLNT_SHAREMODE_SHARED,
               AUDCLNT_STREAMFLAGS_EVENTCALLBACK | AUDCLNT_STREAMFLAGS_NOPERSIST,
               0, 0, (WAVEFORMATEX*)&wf, NULL);
#else
         hr = client->lpVtbl->Initialize(client, AUDCLNT_SHAREMODE_SHARED,
               AUDCLNT_STREAMFLAGS_EVENTCALLBACK | AUDCLNT_STREAMFLAGS_NOPERSIST,
               0, 0, (WAVEFORMATEX*)&wf, NULL);
#endif

         if (hr == AUDCLNT_E_ALREADY_INITIALIZED)
         {
            HRESULT hr;
            IFACE_RELEASE(client);
            hr           = _IMMDevice_Activate(device,
                  IID_IAudioClient,
                  CLSCTX_ALL, NULL, (void**)&client);
            if (FAILED(hr))
               return NULL;

#ifdef __cplusplus
            hr = client->Initialize(AUDCLNT_SHAREMODE_SHARED,
                  AUDCLNT_STREAMFLAGS_EVENTCALLBACK | AUDCLNT_STREAMFLAGS_NOPERSIST,
                  0, 0, (WAVEFORMATEX*)&wf, NULL);
#else
            hr = client->lpVtbl->Initialize(client, AUDCLNT_SHAREMODE_SHARED,
                  AUDCLNT_STREAMFLAGS_EVENTCALLBACK | AUDCLNT_STREAMFLAGS_NOPERSIST,
                  0, 0, (WAVEFORMATEX*)&wf, NULL);
#endif
         }
         if (hr != AUDCLNT_E_UNSUPPORTED_FORMAT)
         {
            i = 2; /* break from outer loop too */
            break;
         }

         RARCH_WARN("[WASAPI]: Unsupported format.\n");
         rate_res = wasapi_pref_rate(j);
         if (rate_res == *rate) /* requested rate is allready tested */
            rate_res = wasapi_pref_rate(++j); /* skip it */
      }
   }

   if (FAILED(hr))
      goto error;

   *float_fmt = float_fmt_res;
   *rate      = rate_res;

   return client;

error:
   IFACE_RELEASE(client);

   return NULL;
}