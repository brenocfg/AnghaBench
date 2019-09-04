#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct fdop {struct fdop* next; } ;
struct TYPE_3__ {struct fdop* __actions; } ;
typedef  TYPE_1__ posix_spawn_file_actions_t ;

/* Variables and functions */
 int /*<<< orphan*/  free (struct fdop*) ; 

int posix_spawn_file_actions_destroy(posix_spawn_file_actions_t *fa)
{
	struct fdop *op = fa->__actions, *next;
	while (op) {
		next = op->next;
		free(op);
		op = next;
	}
	return 0;
}