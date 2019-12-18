#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int maxentities; TYPE_2__* entities; int /*<<< orphan*/  loaded; } ;
struct TYPE_4__ {scalar_t__ valid; } ;
struct TYPE_5__ {TYPE_1__ i; } ;

/* Variables and functions */
 TYPE_3__ aasworld ; 

int AAS_NextEntity(int entnum)
{
	if (!aasworld.loaded) return 0;

	if (entnum < 0) entnum = -1;
	while(++entnum < aasworld.maxentities)
	{
		if (aasworld.entities[entnum].i.valid) return entnum;
	} //end while
	return 0;
}