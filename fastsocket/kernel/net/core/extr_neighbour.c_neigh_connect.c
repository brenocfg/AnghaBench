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
struct neighbour {TYPE_1__* ops; struct hh_cache* hh; int /*<<< orphan*/  output; } ;
struct hh_cache {int /*<<< orphan*/  hh_output; struct hh_cache* hh_next; } ;
struct TYPE_2__ {int /*<<< orphan*/  hh_output; int /*<<< orphan*/  connected_output; } ;

/* Variables and functions */
 int /*<<< orphan*/  NEIGH_PRINTK2 (char*,struct neighbour*) ; 

__attribute__((used)) static void neigh_connect(struct neighbour *neigh)
{
	struct hh_cache *hh;

	NEIGH_PRINTK2("neigh %p is connected.\n", neigh);

	neigh->output = neigh->ops->connected_output;

	for (hh = neigh->hh; hh; hh = hh->hh_next)
		hh->hh_output = neigh->ops->hh_output;
}