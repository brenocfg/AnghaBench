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
struct xencomm_handle {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  XENCOMM_MINI_ALIGNED (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  xc_area ; 
 int xencomm_arch_hypercall_grant_table_op (unsigned int,struct xencomm_handle*,unsigned int) ; 
 int xencommize_grant_table_op (int /*<<< orphan*/ *,unsigned int,void*,unsigned int,struct xencomm_handle**) ; 

int
xencomm_hypercall_grant_table_op(unsigned int cmd, void *op,
				 unsigned int count)
{
	int rc;
	struct xencomm_handle *desc;
	XENCOMM_MINI_ALIGNED(xc_area, 2);

	rc = xencommize_grant_table_op(&xc_area, cmd, op, count, &desc);
	if (rc)
		return rc;

	return xencomm_arch_hypercall_grant_table_op(cmd, desc, count);
}