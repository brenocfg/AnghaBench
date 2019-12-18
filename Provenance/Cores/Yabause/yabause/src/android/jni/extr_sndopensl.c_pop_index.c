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
 size_t queue_head ; 

int pop_index()
{
   int val = index_queue[queue_head];
   queue_head++;      
   if( queue_head >= MAX_QUEUE ) queue_head = 0;
   return val;
}