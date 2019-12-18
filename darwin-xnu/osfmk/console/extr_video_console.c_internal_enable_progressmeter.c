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
typedef  void* boolean_t ;

/* Variables and functions */
 void* FALSE ; 
 int /*<<< orphan*/  IORecordProgressBackbuffer (void*,int,int /*<<< orphan*/ ) ; 
 void* TRUE ; 
 int /*<<< orphan*/  gc_acquired ; 
 scalar_t__ gc_enabled ; 
 int /*<<< orphan*/  gc_graphics_boot ; 
 int kDataAlpha ; 
 int kDataBack ; 
 int kProgressBarHeight ; 
 int kProgressBarWidth ; 
 int kProgressMeterKernel ; 
 int kProgressMeterOff ; 
 int kProgressMeterUser ; 
 int kSave ; 
 void* kalloc (int) ; 
 int /*<<< orphan*/  kfree (void*,int) ; 
 int /*<<< orphan*/  simple_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  simple_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  splhigh () ; 
 int /*<<< orphan*/  splx (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vc_draw_progress_meter (int,int /*<<< orphan*/ ,int,scalar_t__) ; 
 int /*<<< orphan*/  vc_progress_lock ; 
 int /*<<< orphan*/  vc_progress_white ; 
 void* vc_progressmeter_backbuffer ; 
 scalar_t__ vc_progressmeter_drawn ; 
 int vc_progressmeter_enable ; 
 int vc_uiscale ; 

__attribute__((used)) static void
internal_enable_progressmeter(int new_value)
{
    spl_t     s;
    void    * new_buffer;
    boolean_t stashBackbuffer;

    stashBackbuffer = FALSE;
    new_buffer = NULL;
    if (new_value)
    {
	new_buffer = kalloc((kProgressBarWidth * vc_uiscale) 
		            * (kProgressBarHeight * vc_uiscale) * sizeof(int));
    }

    s = splhigh();
    simple_lock(&vc_progress_lock);

    if (kProgressMeterUser == new_value)
    {
	if (gc_enabled || !gc_acquired || !gc_graphics_boot
	 || (kProgressMeterKernel == vc_progressmeter_enable)) new_value = vc_progressmeter_enable;
    }

    if (new_value != vc_progressmeter_enable)
    {
	if (new_value)
	{
	    if (kProgressMeterOff == vc_progressmeter_enable)
	    {
		vc_progressmeter_backbuffer = new_buffer;
		vc_draw_progress_meter(kDataAlpha | kSave, 0, (kProgressBarWidth * vc_uiscale), 0);
		new_buffer = NULL;
		vc_progressmeter_drawn = 0;
	    }
	    vc_progressmeter_enable = new_value;
	}
	else if (vc_progressmeter_backbuffer)
	{
	    if (kProgressMeterUser == vc_progressmeter_enable)
	    {
		vc_draw_progress_meter(kDataBack, 0, (kProgressBarWidth * vc_uiscale), vc_progressmeter_drawn);
	    }
	    else stashBackbuffer = TRUE;
	    new_buffer = vc_progressmeter_backbuffer;
	    vc_progressmeter_backbuffer = NULL;
	    vc_progressmeter_enable = FALSE;
	}
    }

    simple_unlock(&vc_progress_lock);
    splx(s);

    if (new_buffer)
    {
	if (stashBackbuffer) IORecordProgressBackbuffer(new_buffer, 
	    		                                (kProgressBarWidth * vc_uiscale) 
	    		                                * (kProgressBarHeight * vc_uiscale) 
	    		                                * sizeof(int),
	    		                                vc_progress_white);
	kfree(new_buffer, (kProgressBarWidth * vc_uiscale) 
			* (kProgressBarHeight * vc_uiscale) * sizeof(int));
    }
}