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
struct serio {int dummy; } ;
struct hil_dev {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  input_unregister_device (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct hil_dev*) ; 
 int /*<<< orphan*/  serio_close (struct serio*) ; 
 struct hil_dev* serio_get_drvdata (struct serio*) ; 
 int /*<<< orphan*/  serio_set_drvdata (struct serio*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void hil_dev_disconnect(struct serio *serio)
{
	struct hil_dev *dev = serio_get_drvdata(serio);

	BUG_ON(dev == NULL);

	serio_close(serio);
	input_unregister_device(dev->dev);
	serio_set_drvdata(serio, NULL);
	kfree(dev);
}