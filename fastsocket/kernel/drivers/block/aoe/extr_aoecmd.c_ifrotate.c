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
struct aoetgt {struct aoeif* ifp; struct aoeif* ifs; } ;
struct aoeif {int /*<<< orphan*/ * nd; } ;

/* Variables and functions */
 size_t NAOEIFS ; 

__attribute__((used)) static struct aoeif *
ifrotate(struct aoetgt *t)
{
	struct aoeif *ifp;

	ifp = t->ifp;
	ifp++;
	if (ifp >= &t->ifs[NAOEIFS] || ifp->nd == NULL)
		ifp = t->ifs;
	if (ifp->nd == NULL)
		return NULL;
	return t->ifp = ifp;
}