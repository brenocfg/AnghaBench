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
struct sunkbd {int /*<<< orphan*/  dev; } ;
struct serio {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  input_unregister_device (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct sunkbd*) ; 
 int /*<<< orphan*/  serio_close (struct serio*) ; 
 struct sunkbd* serio_get_drvdata (struct serio*) ; 
 int /*<<< orphan*/  serio_set_drvdata (struct serio*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sunkbd_enable (struct sunkbd*,int) ; 

__attribute__((used)) static void sunkbd_disconnect(struct serio *serio)
{
	struct sunkbd *sunkbd = serio_get_drvdata(serio);

	sunkbd_enable(sunkbd, false);
	input_unregister_device(sunkbd->dev);
	serio_close(serio);
	serio_set_drvdata(serio, NULL);
	kfree(sunkbd);
}