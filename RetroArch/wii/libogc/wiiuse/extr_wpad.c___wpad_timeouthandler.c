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
typedef  int /*<<< orphan*/  syswd_t ;
struct wiimote_t {int dummy; } ;
struct _wpad_cb {scalar_t__ idle_time; struct wiimote_t* wm; } ;
typedef  size_t s32 ;

/* Variables and functions */
 scalar_t__ WIIMOTE_IS_SET (struct wiimote_t*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WIIMOTE_STATE_CONNECTED ; 
 size_t WPAD_MAX_WIIMOTES ; 
 scalar_t__ __wpad_idletimeout ; 
 int /*<<< orphan*/  __wpads_active ; 
 struct _wpad_cb* __wpdcb ; 
 int /*<<< orphan*/  _thread_dispatch_disable_level ; 
 int /*<<< orphan*/  wiiuse_disconnect (struct wiimote_t*) ; 

__attribute__((used)) static void __wpad_timeouthandler(syswd_t alarm,void *cbarg)
{
	s32 i;
	struct wiimote_t *wm = NULL;
	struct _wpad_cb *wpdcb = NULL;

	if(!__wpads_active) return;

   ++_thread_dispatch_disable_level;
	for(i=0;i<WPAD_MAX_WIIMOTES;i++) {
		wpdcb = &__wpdcb[i];
		wm = wpdcb->wm;
		if(wm && WIIMOTE_IS_SET(wm,WIIMOTE_STATE_CONNECTED)) {
			wpdcb->idle_time++;
			if(wpdcb->idle_time>=__wpad_idletimeout) {
				wpdcb->idle_time = 0;
				wiiuse_disconnect(wm);
			}
		}
	}
   --_thread_dispatch_disable_level;
}