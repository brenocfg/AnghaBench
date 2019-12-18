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
struct v4l2_standard {int dummy; } ;
struct pvr2_hdw {unsigned int std_enum_cnt; int /*<<< orphan*/  big_lock; scalar_t__ std_defs; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  LOCK_GIVE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LOCK_TAKE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (struct v4l2_standard*,scalar_t__,int) ; 

int pvr2_hdw_get_stdenum_value(struct pvr2_hdw *hdw,
			       struct v4l2_standard *std,
			       unsigned int idx)
{
	int ret = -EINVAL;
	if (!idx) return ret;
	LOCK_TAKE(hdw->big_lock); do {
		if (idx >= hdw->std_enum_cnt) break;
		idx--;
		memcpy(std,hdw->std_defs+idx,sizeof(*std));
		ret = 0;
	} while (0); LOCK_GIVE(hdw->big_lock);
	return ret;
}