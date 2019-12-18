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
struct serio_raw {int /*<<< orphan*/  wait; int /*<<< orphan*/ * serio; } ;
struct serio {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  serio_close (struct serio*) ; 
 struct serio_raw* serio_get_drvdata (struct serio*) ; 
 int /*<<< orphan*/  serio_raw_cleanup (struct serio_raw*) ; 
 int /*<<< orphan*/  serio_raw_mutex ; 
 int /*<<< orphan*/  serio_set_drvdata (struct serio*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wake_up_interruptible (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void serio_raw_disconnect(struct serio *serio)
{
	struct serio_raw *serio_raw;

	mutex_lock(&serio_raw_mutex);

	serio_raw = serio_get_drvdata(serio);

	serio_close(serio);
	serio_set_drvdata(serio, NULL);

	serio_raw->serio = NULL;
	if (!serio_raw_cleanup(serio_raw))
		wake_up_interruptible(&serio_raw->wait);

	mutex_unlock(&serio_raw_mutex);
}