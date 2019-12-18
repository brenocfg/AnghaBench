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
struct mtouch {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  input_get_device (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  input_put_device (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  input_unregister_device (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct mtouch*) ; 
 int /*<<< orphan*/  serio_close (struct serio*) ; 
 struct mtouch* serio_get_drvdata (struct serio*) ; 
 int /*<<< orphan*/  serio_set_drvdata (struct serio*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void mtouch_disconnect(struct serio *serio)
{
	struct mtouch* mtouch = serio_get_drvdata(serio);

	input_get_device(mtouch->dev);
	input_unregister_device(mtouch->dev);
	serio_close(serio);
	serio_set_drvdata(serio, NULL);
	input_put_device(mtouch->dev);
	kfree(mtouch);
}