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
struct pvr2_ctrl {int /*<<< orphan*/  hdw; } ;

/* Variables and functions */
 int /*<<< orphan*/  pvr2_hdw_set_cur_freq (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int ctrl_freq_set(struct pvr2_ctrl *cptr,int m,int v)
{
	pvr2_hdw_set_cur_freq(cptr->hdw,v);
	return 0;
}