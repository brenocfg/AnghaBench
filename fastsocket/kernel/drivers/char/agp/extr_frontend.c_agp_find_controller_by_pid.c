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
struct agp_controller {scalar_t__ pid; struct agp_controller* next; } ;
typedef  scalar_t__ pid_t ;
struct TYPE_2__ {struct agp_controller* controllers; } ;

/* Variables and functions */
 TYPE_1__ agp_fe ; 

__attribute__((used)) static struct agp_controller *agp_find_controller_by_pid(pid_t id)
{
	struct agp_controller *controller;

	controller = agp_fe.controllers;

	while (controller != NULL) {
		if (controller->pid == id)
			return controller;
		controller = controller->next;
	}

	return NULL;
}