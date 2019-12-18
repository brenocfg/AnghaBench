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
struct pnp_id {struct pnp_id* next; } ;
struct pnp_dev {struct pnp_id* id; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct pnp_id*) ; 

__attribute__((used)) static void pnp_free_ids(struct pnp_dev *dev)
{
	struct pnp_id *id;
	struct pnp_id *next;

	id = dev->id;
	while (id) {
		next = id->next;
		kfree(id);
		id = next;
	}
}