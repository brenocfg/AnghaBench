#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {struct TYPE_5__* next; struct TYPE_5__* prev; } ;
typedef  TYPE_1__ bot_consolemessage_t ;

/* Variables and functions */
 int /*<<< orphan*/  FreeMemory (TYPE_1__*) ; 
 scalar_t__ GetClearedHunkMemory (int) ; 
 scalar_t__ LibVarValue (char*,char*) ; 
 TYPE_1__* consolemessageheap ; 
 TYPE_1__* freeconsolemessages ; 

void InitConsoleMessageHeap(void)
{
	int i, max_messages;

	if (consolemessageheap) FreeMemory(consolemessageheap);
	//
	max_messages = (int) LibVarValue("max_messages", "1024");
	consolemessageheap = (bot_consolemessage_t *) GetClearedHunkMemory(max_messages *
												sizeof(bot_consolemessage_t));
	consolemessageheap[0].prev = NULL;
	consolemessageheap[0].next = &consolemessageheap[1];
	for (i = 1; i < max_messages-1; i++)
	{
		consolemessageheap[i].prev = &consolemessageheap[i - 1];
		consolemessageheap[i].next = &consolemessageheap[i + 1];
	} //end for
	consolemessageheap[max_messages-1].prev = &consolemessageheap[max_messages-2];
	consolemessageheap[max_messages-1].next = NULL;
	//pointer to the free console messages
	freeconsolemessages = consolemessageheap;
}