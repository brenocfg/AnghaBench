#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {struct TYPE_3__* next_ent; struct TYPE_3__* prev_ent; } ;
typedef  TYPE_1__ aas_link_t ;
struct TYPE_4__ {int linkheapsize; TYPE_1__* linkheap; TYPE_1__* freelinks; } ;

/* Variables and functions */
 scalar_t__ GetHunkMemory (int) ; 
 scalar_t__ LibVarValue (char*,char*) ; 
 TYPE_2__ aasworld ; 
 int numaaslinks ; 

void AAS_InitAASLinkHeap(void)
{
	int i, max_aaslinks;

	max_aaslinks = aasworld.linkheapsize;
	//if there's no link heap present
	if (!aasworld.linkheap)
	{
#ifdef BSPC
		max_aaslinks = 6144;
#else
		max_aaslinks = (int) LibVarValue("max_aaslinks", "6144");
#endif
		if (max_aaslinks < 0) max_aaslinks = 0;
		aasworld.linkheapsize = max_aaslinks;
		aasworld.linkheap = (aas_link_t *) GetHunkMemory(max_aaslinks * sizeof(aas_link_t));
	} //end if
	//link the links on the heap
	aasworld.linkheap[0].prev_ent = NULL;
	aasworld.linkheap[0].next_ent = &aasworld.linkheap[1];
	for (i = 1; i < max_aaslinks-1; i++)
	{
		aasworld.linkheap[i].prev_ent = &aasworld.linkheap[i - 1];
		aasworld.linkheap[i].next_ent = &aasworld.linkheap[i + 1];
	} //end for
	aasworld.linkheap[max_aaslinks-1].prev_ent = &aasworld.linkheap[max_aaslinks-2];
	aasworld.linkheap[max_aaslinks-1].next_ent = NULL;
	//pointer to the first free link
	aasworld.freelinks = &aasworld.linkheap[0];
	//
	numaaslinks = max_aaslinks;
}