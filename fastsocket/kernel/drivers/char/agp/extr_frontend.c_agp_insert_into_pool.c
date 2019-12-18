#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct agp_memory {struct agp_memory* next; struct agp_memory* prev; } ;
struct TYPE_4__ {TYPE_1__* current_controller; } ;
struct TYPE_3__ {struct agp_memory* pool; } ;

/* Variables and functions */
 TYPE_2__ agp_fe ; 

__attribute__((used)) static void agp_insert_into_pool(struct agp_memory * temp)
{
	struct agp_memory *prev;

	prev = agp_fe.current_controller->pool;

	if (prev != NULL) {
		prev->prev = temp;
		temp->next = prev;
	}
	agp_fe.current_controller->pool = temp;
}