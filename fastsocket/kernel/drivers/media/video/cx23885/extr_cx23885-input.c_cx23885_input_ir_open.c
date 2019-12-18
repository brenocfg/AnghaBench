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
struct rc_dev {struct cx23885_kernel_ir* priv; } ;
struct cx23885_kernel_ir {int /*<<< orphan*/ * cx; } ;

/* Variables and functions */
 int ENODEV ; 
 int cx23885_input_ir_start (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int cx23885_input_ir_open(struct rc_dev *rc)
{
	struct cx23885_kernel_ir *kernel_ir = rc->priv;

	if (kernel_ir->cx == NULL)
		return -ENODEV;

	return cx23885_input_ir_start(kernel_ir->cx);
}