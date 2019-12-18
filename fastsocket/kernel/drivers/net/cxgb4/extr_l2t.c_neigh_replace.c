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
struct neighbour {int dummy; } ;
struct l2t_entry {struct neighbour* neigh; } ;

/* Variables and functions */
 int /*<<< orphan*/  neigh_hold (struct neighbour*) ; 
 int /*<<< orphan*/  neigh_release (struct neighbour*) ; 

__attribute__((used)) static void neigh_replace(struct l2t_entry *e, struct neighbour *n)
{
	neigh_hold(n);
	if (e->neigh)
		neigh_release(e->neigh);
	e->neigh = n;
}