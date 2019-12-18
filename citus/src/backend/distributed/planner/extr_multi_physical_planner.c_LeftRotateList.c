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
typedef  scalar_t__ uint32 ;
typedef  int /*<<< orphan*/  List ;

/* Variables and functions */
 int /*<<< orphan*/ * lappend (int /*<<< orphan*/ *,void*) ; 
 void* linitial (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * list_copy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * list_delete_first (int /*<<< orphan*/ *) ; 

__attribute__((used)) static List *
LeftRotateList(List *list, uint32 rotateCount)
{
	List *rotatedList = list_copy(list);

	uint32 rotateIndex = 0;
	for (rotateIndex = 0; rotateIndex < rotateCount; rotateIndex++)
	{
		void *firstElement = linitial(rotatedList);

		rotatedList = list_delete_first(rotatedList);
		rotatedList = lappend(rotatedList, firstElement);
	}

	return rotatedList;
}