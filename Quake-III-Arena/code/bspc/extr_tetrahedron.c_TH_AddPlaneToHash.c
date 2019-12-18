#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {struct TYPE_4__* hashnext; int /*<<< orphan*/  dist; } ;
typedef  TYPE_1__ th_plane_t ;
struct TYPE_5__ {TYPE_1__** planehash; } ;

/* Variables and functions */
 int PLANEHASH_SIZE ; 
 scalar_t__ fabs (int /*<<< orphan*/ ) ; 
 TYPE_2__ thworld ; 

void TH_AddPlaneToHash(th_plane_t *p)
{
	int hash;

	hash = (int)fabs(p->dist) / 8;
	hash &= (PLANEHASH_SIZE-1);

	p->hashnext = thworld.planehash[hash];
	thworld.planehash[hash] = p;
}