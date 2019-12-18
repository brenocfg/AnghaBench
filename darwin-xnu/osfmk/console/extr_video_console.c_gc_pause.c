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
typedef  int /*<<< orphan*/  spl_t ;
typedef  scalar_t__ boolean_t ;

/* Variables and functions */
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  VCPUTC_LOCK_LOCK () ; 
 int /*<<< orphan*/  VCPUTC_LOCK_UNLOCK () ; 
 int /*<<< orphan*/  console_is_serial () ; 
 int disableConsoleOutput ; 
 int gc_enabled ; 
 scalar_t__ gc_paused_progress ; 
 int /*<<< orphan*/  simple_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  simple_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  splhigh () ; 
 int /*<<< orphan*/  splx (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  thread_call_enter_delayed (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vc_progress_call ; 
 int /*<<< orphan*/  vc_progress_deadline ; 
 scalar_t__ vc_progress_enable ; 
 int /*<<< orphan*/  vc_progress_lock ; 
 int vc_progress_withmeter ; 
 int /*<<< orphan*/  vc_progressmeter_call ; 
 int /*<<< orphan*/  vc_progressmeter_deadline ; 

__attribute__((used)) static void
gc_pause( boolean_t pause, boolean_t graphics_now )
{
	spl_t s;

	s = splhigh( );
	VCPUTC_LOCK_LOCK( );

    disableConsoleOutput = (pause && !console_is_serial());
    gc_enabled           = (!pause && !graphics_now);

    VCPUTC_LOCK_UNLOCK( );

    simple_lock(&vc_progress_lock);

    if (pause) 
    {
        gc_paused_progress = vc_progress_enable;
	vc_progress_enable = FALSE;
    }
    else vc_progress_enable = gc_paused_progress;

    if (vc_progress_enable)
    {
#if !CONFIG_EMBEDDED
	if (1 & vc_progress_withmeter) thread_call_enter_delayed(&vc_progressmeter_call, vc_progressmeter_deadline);
	else                           
#endif /* !CONFIG_EMBEDDED */
	thread_call_enter_delayed(&vc_progress_call, vc_progress_deadline);
    }

    simple_unlock(&vc_progress_lock);
    splx(s);
}