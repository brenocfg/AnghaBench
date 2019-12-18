#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {size_t engine_buffer_size; int frame_size; int /*<<< orphan*/  client; scalar_t__ buffer; } ;
typedef  TYPE_1__ wasapi_t ;
typedef  int UINT32 ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _IAudioClient_GetCurrentPadding (int /*<<< orphan*/ ,int*) ; 
 size_t fifo_write_avail (scalar_t__) ; 

__attribute__((used)) static size_t wasapi_write_avail(void *wh)
{
   HRESULT hr;
   wasapi_t *w    = (wasapi_t*)wh;
   UINT32 padding = 0;

   if (w->buffer)
      return fifo_write_avail(w->buffer);

   hr = _IAudioClient_GetCurrentPadding(w->client, &padding);
   if (FAILED(hr))
      return 0;

   return w->engine_buffer_size - padding * w->frame_size;
}