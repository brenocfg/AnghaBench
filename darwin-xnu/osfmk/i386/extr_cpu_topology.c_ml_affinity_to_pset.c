#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ num; int /*<<< orphan*/  pset; struct TYPE_3__* next; } ;
typedef  TYPE_1__ x86_affinity_set_t ;
typedef  scalar_t__ uint32_t ;
typedef  int /*<<< orphan*/  processor_set_t ;

/* Variables and functions */
 int /*<<< orphan*/  PROCESSOR_SET_NULL ; 
 TYPE_1__* x86_affinities ; 

processor_set_t
ml_affinity_to_pset(uint32_t affinity_num) 
{
	x86_affinity_set_t	*aset;

	for (aset = x86_affinities; aset != NULL; aset = aset->next) {
		if (affinity_num == aset->num)
			break;
	}
	return (aset == NULL) ? PROCESSOR_SET_NULL : aset->pset;
}