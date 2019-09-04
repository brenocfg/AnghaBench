#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {TYPE_1__* First; TYPE_1__* Last; } ;
struct TYPE_6__ {struct TYPE_6__* Next; struct TYPE_6__* Prev; } ;
typedef  TYPE_1__ SFG_Node ;
typedef  TYPE_2__ SFG_List ;

/* Variables and functions */

void fgListInsert(SFG_List *list, SFG_Node *next, SFG_Node *node)
{
    SFG_Node *prev;

    if( (node->Next = next) )
    {
        prev = next->Prev;
        next->Prev = node;
    }
    else
    {
        prev = list->Last;
        list->Last = node;
    }

    if( (node->Prev = prev) )
        prev->Next = node;
    else
        list->First = node;
}