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
struct pvr2_hdw {int flag_ok; } ;

/* Variables and functions */
 int FX2CMD_HCW_DEMOD_RESETIN ; 
 int pvr2_issue_simple_cmd (struct pvr2_hdw*,int) ; 

__attribute__((used)) static int pvr2_hdw_cmd_hcw_demod_reset(struct pvr2_hdw *hdw, int onoff)
{
	hdw->flag_ok = !0;
	return pvr2_issue_simple_cmd(hdw,
				     FX2CMD_HCW_DEMOD_RESETIN |
				     (1 << 8) |
				     ((onoff ? 1 : 0) << 16));
}