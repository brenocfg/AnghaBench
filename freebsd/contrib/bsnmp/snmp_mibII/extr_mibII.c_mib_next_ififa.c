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
struct mibifa {scalar_t__ ifindex; } ;

/* Variables and functions */
 struct mibifa* TAILQ_NEXT (struct mibifa*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  link ; 

struct mibifa *
mib_next_ififa(struct mibifa *ifa0)
{
	struct mibifa *ifa;

	ifa = ifa0;
	while ((ifa = TAILQ_NEXT(ifa, link)) != NULL)
		if (ifa->ifindex == ifa0->ifindex)
			return (ifa);
	return (NULL);
}