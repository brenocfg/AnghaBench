#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  dd_node; struct TYPE_4__* dd_name; struct TYPE_4__* dd_next; } ;
typedef  TYPE_1__ dt_decl_t ;

/* Variables and functions */
 int /*<<< orphan*/  dt_node_list_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 

void
dt_decl_free(dt_decl_t *ddp)
{
	dt_decl_t *ndp;

	for (; ddp != NULL; ddp = ndp) {
		ndp = ddp->dd_next;
		free(ddp->dd_name);
		dt_node_list_free(&ddp->dd_node);
		free(ddp);
	}
}