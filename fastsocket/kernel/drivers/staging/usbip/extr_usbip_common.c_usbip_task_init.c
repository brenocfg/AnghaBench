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
struct usbip_task {char* name; void (* loop_ops ) (struct usbip_task*) ;int /*<<< orphan*/  thread_done; int /*<<< orphan*/ * thread; } ;

/* Variables and functions */
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 

void usbip_task_init(struct usbip_task *ut, char *name,
		void (*loop_ops)(struct usbip_task *))
{
	ut->thread = NULL;
	init_completion(&ut->thread_done);
	ut->name = name;
	ut->loop_ops = loop_ops;
}