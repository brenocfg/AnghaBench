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
struct ctl_cb {scalar_t__ mtx; } ;

/* Variables and functions */
 int /*<<< orphan*/  FREE (struct ctl_cb*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  M_TEMP ; 
 int /*<<< orphan*/  ctl_lck_grp ; 
 int /*<<< orphan*/  lck_mtx_free (scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
kcb_delete(struct ctl_cb *kcb)
{
	if (kcb != 0) {
		if (kcb->mtx != 0)
			lck_mtx_free(kcb->mtx, ctl_lck_grp);
		FREE(kcb, M_TEMP);
	}
}