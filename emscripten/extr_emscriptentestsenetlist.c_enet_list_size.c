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
typedef  scalar_t__ ENetListIterator ;
typedef  int /*<<< orphan*/  ENetList ;

/* Variables and functions */
 scalar_t__ enet_list_begin (int /*<<< orphan*/ *) ; 
 scalar_t__ enet_list_end (int /*<<< orphan*/ *) ; 
 scalar_t__ enet_list_next (scalar_t__) ; 

size_t
enet_list_size (ENetList * list)
{
   size_t size = 0;
   ENetListIterator position;

   for (position = enet_list_begin (list);
        position != enet_list_end (list);
        position = enet_list_next (position))
     ++ size;
   
   return size;
}