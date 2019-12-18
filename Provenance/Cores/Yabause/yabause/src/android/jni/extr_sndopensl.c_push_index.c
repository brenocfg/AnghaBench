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

/* Variables and functions */
 size_t MAX_QUEUE ; 
 int* index_queue ; 
 size_t queue_tail ; 

void push_index( int index )
{
   index_queue[queue_tail] = index;
   queue_tail++;      
   if( queue_tail >= MAX_QUEUE ) queue_tail = 0;
}