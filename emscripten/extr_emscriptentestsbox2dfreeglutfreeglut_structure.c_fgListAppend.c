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
struct TYPE_6__ {TYPE_1__* Last; TYPE_1__* First; } ;
struct TYPE_5__ {struct TYPE_5__* Next; struct TYPE_5__* Prev; } ;
typedef  TYPE_1__ SFG_Node ;
typedef  TYPE_2__ SFG_List ;

/* Variables and functions */

void fgListAppend(SFG_List *list, SFG_Node *node)
{
    if ( list->Last )
    {
        SFG_Node *ln = (SFG_Node *) list->Last;
        ln->Next = node;
        node->Prev = ln;
    }
    else
    {
        node->Prev = NULL;
        list->First = node;
    }

    node->Next = NULL;
    list->Last = node;
}