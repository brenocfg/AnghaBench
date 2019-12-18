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
struct em28xx_IR {int /*<<< orphan*/  rc; } ;
struct em28xx {struct em28xx_IR* ir; } ;

/* Variables and functions */
 int /*<<< orphan*/  em28xx_ir_stop (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct em28xx_IR*) ; 
 int /*<<< orphan*/  rc_unregister_device (int /*<<< orphan*/ ) ; 

int em28xx_ir_fini(struct em28xx *dev)
{
	struct em28xx_IR *ir = dev->ir;

	/* skip detach on non attached boards */
	if (!ir)
		return 0;

	em28xx_ir_stop(ir->rc);
	rc_unregister_device(ir->rc);
	kfree(ir);

	/* done */
	dev->ir = NULL;
	return 0;
}