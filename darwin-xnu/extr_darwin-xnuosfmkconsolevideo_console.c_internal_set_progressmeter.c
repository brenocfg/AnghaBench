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

/* Variables and functions */
 int /*<<< orphan*/  kDataAlpha ; 
 int kProgressBarCapWidth ; 
 int kProgressBarWidth ; 
 int kProgressMeterMax ; 
 int /*<<< orphan*/  vc_draw_progress_meter (int /*<<< orphan*/ ,int,int,int) ; 
 int vc_progress_withmeter ; 
 int vc_progressmeter_drawn ; 
 scalar_t__ vc_progressmeter_enable ; 
 int vc_progressmeter_value ; 
 int vc_uiscale ; 

__attribute__((used)) static void
internal_set_progressmeter(int new_value)
{
    int x1, x3;
    int capRedraw;
    // 1 rounded fill, 0 square end
    int style = (0 == (2 & vc_progress_withmeter));

    if ((new_value < 0) || (new_value > kProgressMeterMax)) return;

    if (vc_progressmeter_enable)
    {
	vc_progressmeter_value = new_value;

	capRedraw = (style ? (kProgressBarCapWidth * vc_uiscale) : 0);
	x3 = (((kProgressBarWidth * vc_uiscale) - 2 * capRedraw) * vc_progressmeter_value) / kProgressMeterMax;
	x3 += (2 * capRedraw);

	if (x3 > vc_progressmeter_drawn)
	{
	    x1 = capRedraw;
	    if (x1 > vc_progressmeter_drawn) x1 = vc_progressmeter_drawn;
	    vc_draw_progress_meter(kDataAlpha, vc_progressmeter_drawn - x1, x3, x3);
        }
	else
	{
	    vc_draw_progress_meter(kDataAlpha, x3 - capRedraw, vc_progressmeter_drawn, x3);
	}
	vc_progressmeter_drawn = x3;
    }
}