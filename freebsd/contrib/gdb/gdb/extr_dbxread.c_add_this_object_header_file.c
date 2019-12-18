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
 int n_this_object_header_files ; 
 int* this_object_header_files ; 
 scalar_t__ xrealloc (char*,int) ; 

__attribute__((used)) static void
add_this_object_header_file (int i)
{
  if (n_this_object_header_files == n_allocated_this_object_header_files)
    {
      n_allocated_this_object_header_files *= 2;
      this_object_header_files
	= (int *) xrealloc ((char *) this_object_header_files,
		       n_allocated_this_object_header_files * sizeof (int));
    }

  this_object_header_files[n_this_object_header_files++] = i;
}