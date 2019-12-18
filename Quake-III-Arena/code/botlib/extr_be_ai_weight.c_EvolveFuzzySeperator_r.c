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
struct TYPE_3__ {scalar_t__ type; scalar_t__ weight; double maxweight; double minweight; struct TYPE_3__* next; struct TYPE_3__* child; } ;
typedef  TYPE_1__ fuzzyseperator_t ;

/* Variables and functions */
 scalar_t__ WT_BALANCE ; 
 double crandom () ; 
 double random () ; 

void EvolveFuzzySeperator_r(fuzzyseperator_t *fs)
{
	if (fs->child)
	{
		EvolveFuzzySeperator_r(fs->child);
	} //end if
	else if (fs->type == WT_BALANCE)
	{
		//every once in a while an evolution leap occurs, mutation
		if (random() < 0.01) fs->weight += crandom() * (fs->maxweight - fs->minweight);
		else fs->weight += crandom() * (fs->maxweight - fs->minweight) * 0.5;
		//modify bounds if necesary because of mutation
		if (fs->weight < fs->minweight) fs->minweight = fs->weight;
		else if (fs->weight > fs->maxweight) fs->maxweight = fs->weight;
	} //end else if
	if (fs->next) EvolveFuzzySeperator_r(fs->next);
}