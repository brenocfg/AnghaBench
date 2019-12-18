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
typedef  int /*<<< orphan*/  weightconfig_t ;
struct TYPE_5__ {int numiteminfo; TYPE_1__* iteminfo; } ;
typedef  TYPE_2__ itemconfig_t ;
struct TYPE_4__ {int /*<<< orphan*/  classname; } ;

/* Variables and functions */
 int FindFuzzyWeight (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ GetClearedMemory (int) ; 
 int /*<<< orphan*/  Log_Write (char*,int,int /*<<< orphan*/ ) ; 

int *ItemWeightIndex(weightconfig_t *iwc, itemconfig_t *ic)
{
	int *index, i;

	//initialize item weight index
	index = (int *) GetClearedMemory(sizeof(int) * ic->numiteminfo);

	for (i = 0; i < ic->numiteminfo; i++)
	{
		index[i] = FindFuzzyWeight(iwc, ic->iteminfo[i].classname);
		if (index[i] < 0)
		{
			Log_Write("item info %d \"%s\" has no fuzzy weight\r\n", i, ic->iteminfo[i].classname);
		} //end if
	} //end for
	return index;
}