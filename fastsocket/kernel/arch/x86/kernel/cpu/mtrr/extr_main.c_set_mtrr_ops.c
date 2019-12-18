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
struct mtrr_ops {size_t vendor; } ;

/* Variables and functions */
 size_t X86_VENDOR_NUM ; 
 struct mtrr_ops** mtrr_ops ; 

void set_mtrr_ops(struct mtrr_ops *ops)
{
	if (ops->vendor && ops->vendor < X86_VENDOR_NUM)
		mtrr_ops[ops->vendor] = ops;
}