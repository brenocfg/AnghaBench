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
struct serio {scalar_t__ child; } ;

/* Variables and functions */
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  serio_destroy_port (scalar_t__) ; 
 int /*<<< orphan*/  serio_disconnect_port (scalar_t__) ; 
 int /*<<< orphan*/  serio_mutex ; 

void serio_unregister_child_port(struct serio *serio)
{
	mutex_lock(&serio_mutex);
	if (serio->child) {
		serio_disconnect_port(serio->child);
		serio_destroy_port(serio->child);
	}
	mutex_unlock(&serio_mutex);
}