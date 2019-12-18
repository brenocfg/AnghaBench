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
struct saa7134_dev {TYPE_1__* remote; } ;
struct rc_dev {struct saa7134_dev* priv; } ;
struct TYPE_2__ {int /*<<< orphan*/  users; } ;

/* Variables and functions */
 int /*<<< orphan*/  __saa7134_ir_stop (struct saa7134_dev*) ; 

__attribute__((used)) static void saa7134_ir_close(struct rc_dev *rc)
{
	struct saa7134_dev *dev = rc->priv;

	dev->remote->users--;
	if (!dev->remote->users)
		__saa7134_ir_stop(dev);
}