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
 int n_allocated_this_object_header_files ; 
 int* this_object_header_files ; 
 scalar_t__ xmalloc (int) ; 

void
init_header_files (void)
{
  n_allocated_this_object_header_files = 10;
  this_object_header_files = (int *) xmalloc (10 * sizeof (int));
}