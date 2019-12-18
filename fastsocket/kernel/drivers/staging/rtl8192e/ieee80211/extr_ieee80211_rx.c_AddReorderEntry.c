#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct list_head {struct list_head* next; struct list_head* prev; } ;
struct TYPE_6__ {struct list_head List; int /*<<< orphan*/  SeqNum; } ;
struct TYPE_5__ {struct list_head RxPendingPktList; } ;
typedef  TYPE_1__* PRX_TS_RECORD ;
typedef  TYPE_2__* PRX_REORDER_ENTRY ;

/* Variables and functions */
 int /*<<< orphan*/  List ; 
 int /*<<< orphan*/  RX_REORDER_ENTRY ; 
 scalar_t__ SN_EQUAL (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ SN_LESS (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ list_entry (struct list_head*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

bool
AddReorderEntry(
	PRX_TS_RECORD			pTS,
	PRX_REORDER_ENTRY		pReorderEntry
	)
{
	struct list_head *pList = &pTS->RxPendingPktList;
#if  1
	while(pList->next != &pTS->RxPendingPktList)
	{
		if( SN_LESS(pReorderEntry->SeqNum, ((PRX_REORDER_ENTRY)list_entry(pList->next,RX_REORDER_ENTRY,List))->SeqNum) )
		{
			pList = pList->next;
		}
		else if( SN_EQUAL(pReorderEntry->SeqNum, ((PRX_REORDER_ENTRY)list_entry(pList->next,RX_REORDER_ENTRY,List))->SeqNum) )
		{
			return false;
		}
		else
		{
			break;
		}
	}
#endif
	pReorderEntry->List.next = pList->next;
	pReorderEntry->List.next->prev = &pReorderEntry->List;
	pReorderEntry->List.prev = pList;
	pList->next = &pReorderEntry->List;

	return true;
}