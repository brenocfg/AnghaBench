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
struct parport {struct parport* name; TYPE_1__* probe_info; int /*<<< orphan*/  full_list; } ;
struct TYPE_2__ {struct parport* description; struct parport* cmdset; struct parport* model; struct parport* mfr; struct parport* class_name; } ;

/* Variables and functions */
 int /*<<< orphan*/  full_list_lock ; 
 int /*<<< orphan*/  kfree (struct parport*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void free_port (struct parport *port)
{
	int d;
	spin_lock(&full_list_lock);
	list_del(&port->full_list);
	spin_unlock(&full_list_lock);
	for (d = 0; d < 5; d++) {
		kfree(port->probe_info[d].class_name);
		kfree(port->probe_info[d].mfr);
		kfree(port->probe_info[d].model);
		kfree(port->probe_info[d].cmdset);
		kfree(port->probe_info[d].description);
	}

	kfree(port->name);
	kfree(port);
}