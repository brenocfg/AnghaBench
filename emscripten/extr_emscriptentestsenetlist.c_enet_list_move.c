#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {struct TYPE_4__* previous; struct TYPE_4__* next; } ;
typedef  TYPE_1__* ENetListIterator ;

/* Variables and functions */

ENetListIterator
enet_list_move (ENetListIterator position, void * dataFirst, void * dataLast)
{
   ENetListIterator first = (ENetListIterator) dataFirst,
                    last = (ENetListIterator) dataLast;

   first -> previous -> next = last -> next;
   last -> next -> previous = first -> previous;

   first -> previous = position -> previous;
   last -> next = position;

   first -> previous -> next = first;
   position -> previous = last;
    
   return first;
}