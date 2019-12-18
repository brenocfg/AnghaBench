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
typedef  int u32 ;
struct _wpad_cb {int /*<<< orphan*/  sound_alarm; } ;
typedef  size_t s32 ;

/* Variables and functions */
 int /*<<< orphan*/  BTE_Shutdown () ; 
 int /*<<< orphan*/  SYS_RemoveAlarm (int /*<<< orphan*/ ) ; 
 size_t WPAD_MAX_WIIMOTES ; 
 int /*<<< orphan*/  WPAD_STATE_DISABLED ; 
 int /*<<< orphan*/  _CPU_ISR_Disable (int) ; 
 int /*<<< orphan*/  _CPU_ISR_Restore (int) ; 
 int /*<<< orphan*/  __wiiuse_sensorbar_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __wpad_disconnect (struct _wpad_cb*) ; 
 int /*<<< orphan*/  __wpad_timer ; 
 scalar_t__ __wpads_active ; 
 int /*<<< orphan*/  __wpads_inited ; 
 struct _wpad_cb* __wpdcb ; 
 int /*<<< orphan*/  usleep (int) ; 

void WPAD_Shutdown()
{
	s32 i;
	u32 level;
	u32 cnt = 0;
	struct _wpad_cb *wpdcb = NULL;

	_CPU_ISR_Disable(level);

	__wpads_inited = WPAD_STATE_DISABLED;
	SYS_RemoveAlarm(__wpad_timer);
	for(i=0;i<WPAD_MAX_WIIMOTES;i++) {
		wpdcb = &__wpdcb[i];
#ifdef HAVE_WIIUSE_SPEAKER
		SYS_RemoveAlarm(wpdcb->sound_alarm);
#endif
		__wpad_disconnect(wpdcb);
	}

	__wiiuse_sensorbar_enable(0);
	_CPU_ISR_Restore(level);

	while(__wpads_active) {
		usleep(50);
		if(++cnt > 3000) break;
	}

	BTE_Shutdown();
}