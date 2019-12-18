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
 int can_run ; 
 scalar_t__ insert_position ; 
 scalar_t__ read_position ; 

__attribute__((used)) static void btpad_queue_reset(void)
{
   insert_position = 0;
   read_position   = 0;
   can_run         = 1;
}