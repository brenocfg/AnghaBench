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
struct TYPE_2__ {int running; int /*<<< orphan*/  client; } ;
typedef  TYPE_1__ wasapi_t ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _IAudioClient_Stop (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool wasapi_stop(void *wh)
{
   wasapi_t *w = (wasapi_t*)wh;
   HRESULT  hr = _IAudioClient_Stop(w->client);
   if (FAILED(hr))
      return !w->running;

   w->running = false;

   return true;
}