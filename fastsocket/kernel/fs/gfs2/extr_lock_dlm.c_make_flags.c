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
typedef  scalar_t__ u32 ;
struct TYPE_2__ {scalar_t__ sb_lkid; } ;
struct gfs2_glock {int /*<<< orphan*/  gl_flags; TYPE_1__ gl_lksb; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
 scalar_t__ DLM_LKF_ALTCW ; 
 scalar_t__ DLM_LKF_ALTPR ; 
 scalar_t__ DLM_LKF_CONVERT ; 
 scalar_t__ DLM_LKF_HEADQUE ; 
 scalar_t__ DLM_LKF_NOORDER ; 
 scalar_t__ DLM_LKF_NOQUEUE ; 
 scalar_t__ DLM_LKF_NOQUEUEBAST ; 
 scalar_t__ DLM_LKF_QUECVT ; 
 scalar_t__ DLM_LKF_VALBLK ; 
 int const DLM_LOCK_CW ; 
 int const DLM_LOCK_PR ; 
 int /*<<< orphan*/  GLF_BLOCKING ; 
 unsigned int const LM_FLAG_ANY ; 
 unsigned int const LM_FLAG_PRIORITY ; 
 unsigned int const LM_FLAG_TRY ; 
 unsigned int const LM_FLAG_TRY_1CB ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static u32 make_flags(struct gfs2_glock *gl, const unsigned int gfs_flags,
		      const int req)
{
	u32 lkf = DLM_LKF_VALBLK;
	u32 lkid = gl->gl_lksb.sb_lkid;

	if (gfs_flags & LM_FLAG_TRY)
		lkf |= DLM_LKF_NOQUEUE;

	if (gfs_flags & LM_FLAG_TRY_1CB) {
		lkf |= DLM_LKF_NOQUEUE;
		lkf |= DLM_LKF_NOQUEUEBAST;
	}

	if (gfs_flags & LM_FLAG_PRIORITY) {
		lkf |= DLM_LKF_NOORDER;
		lkf |= DLM_LKF_HEADQUE;
	}

	if (gfs_flags & LM_FLAG_ANY) {
		if (req == DLM_LOCK_PR)
			lkf |= DLM_LKF_ALTCW;
		else if (req == DLM_LOCK_CW)
			lkf |= DLM_LKF_ALTPR;
		else
			BUG();
	}

	if (lkid != 0) {
		lkf |= DLM_LKF_CONVERT;
		if (test_bit(GLF_BLOCKING, &gl->gl_flags))
			lkf |= DLM_LKF_QUECVT;
	}

	return lkf;
}