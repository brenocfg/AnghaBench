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
struct neigh_parms {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct neigh_parms*) ; 
 int /*<<< orphan*/  neigh_parms_net (struct neigh_parms*) ; 
 int /*<<< orphan*/  release_net (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void neigh_parms_destroy(struct neigh_parms *parms)
{
	release_net(neigh_parms_net(parms));
	kfree(parms);
}