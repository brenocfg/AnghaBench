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
struct pvr2_hdw {int std_enum_cnt; int std_enum_cur; scalar_t__ std_mask_cur; int std_dirty; TYPE_1__* std_defs; } ;
struct pvr2_ctrl {struct pvr2_hdw* hdw; } ;
struct TYPE_2__ {scalar_t__ id; } ;

/* Variables and functions */
 int EINVAL ; 

__attribute__((used)) static int ctrl_stdenumcur_set(struct pvr2_ctrl *cptr,int m,int v)
{
	struct pvr2_hdw *hdw = cptr->hdw;
	if (v < 0) return -EINVAL;
	if (v > hdw->std_enum_cnt) return -EINVAL;
	hdw->std_enum_cur = v;
	if (!v) return 0;
	v--;
	if (hdw->std_mask_cur == hdw->std_defs[v].id) return 0;
	hdw->std_mask_cur = hdw->std_defs[v].id;
	hdw->std_dirty = !0;
	return 0;
}