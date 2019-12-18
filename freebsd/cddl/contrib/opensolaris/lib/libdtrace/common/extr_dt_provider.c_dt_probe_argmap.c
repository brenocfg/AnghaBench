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
typedef  scalar_t__ uint8_t ;
struct TYPE_4__ {struct TYPE_4__* dn_list; int /*<<< orphan*/ * dn_string; } ;
typedef  TYPE_1__ dt_node_t ;

/* Variables and functions */
 scalar_t__ strcmp (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static uint8_t
dt_probe_argmap(dt_node_t *xnp, dt_node_t *nnp)
{
	uint8_t i;

	for (i = 0; nnp != NULL; i++) {
		if (nnp->dn_string != NULL &&
		    strcmp(nnp->dn_string, xnp->dn_string) == 0)
			break;
		else
			nnp = nnp->dn_list;
	}

	return (i);
}