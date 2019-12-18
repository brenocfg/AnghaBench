#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_5__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct ser_cardstate {int dummy; } ;
struct TYPE_6__ {TYPE_3__* ser; } ;
struct cardstate {int /*<<< orphan*/  write_tasklet; TYPE_1__ hw; int /*<<< orphan*/  minor_index; } ;
struct TYPE_9__ {int /*<<< orphan*/  release; } ;
struct TYPE_7__ {TYPE_5__ dev; int /*<<< orphan*/  id; int /*<<< orphan*/  name; } ;
struct TYPE_8__ {TYPE_2__ dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  GIGASET_MODULENAME ; 
 int /*<<< orphan*/  dev_set_drvdata (TYPE_5__*,struct cardstate*) ; 
 int /*<<< orphan*/  gigaset_device_release ; 
 int /*<<< orphan*/  gigaset_modem_fill ; 
 int /*<<< orphan*/  kfree (TYPE_3__*) ; 
 TYPE_3__* kzalloc (int,int /*<<< orphan*/ ) ; 
 int platform_device_register (TYPE_2__*) ; 
 int /*<<< orphan*/  pr_err (char*,...) ; 
 int /*<<< orphan*/  tasklet_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int gigaset_initcshw(struct cardstate *cs)
{
	int rc;

	if (!(cs->hw.ser = kzalloc(sizeof(struct ser_cardstate), GFP_KERNEL))) {
		pr_err("out of memory\n");
		return 0;
	}

	cs->hw.ser->dev.name = GIGASET_MODULENAME;
	cs->hw.ser->dev.id = cs->minor_index;
	cs->hw.ser->dev.dev.release = gigaset_device_release;
	if ((rc = platform_device_register(&cs->hw.ser->dev)) != 0) {
		pr_err("error %d registering platform device\n", rc);
		kfree(cs->hw.ser);
		cs->hw.ser = NULL;
		return 0;
	}
	dev_set_drvdata(&cs->hw.ser->dev.dev, cs);

	tasklet_init(&cs->write_tasklet,
	             &gigaset_modem_fill, (unsigned long) cs);
	return 1;
}