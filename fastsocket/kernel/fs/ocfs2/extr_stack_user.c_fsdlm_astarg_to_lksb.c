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
struct dlm_lksb {int dummy; } ;
struct TYPE_2__ {struct dlm_lksb lksb_fsdlm; } ;
struct ocfs2_lock_res {TYPE_1__ l_lksb; } ;

/* Variables and functions */

__attribute__((used)) static struct dlm_lksb *fsdlm_astarg_to_lksb(void *astarg)
{
	struct ocfs2_lock_res *res = astarg;
	return &res->l_lksb.lksb_fsdlm;
}