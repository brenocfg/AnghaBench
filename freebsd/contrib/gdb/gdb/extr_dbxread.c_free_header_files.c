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
 scalar_t__ n_allocated_this_object_header_files ; 
 int /*<<< orphan*/ * this_object_header_files ; 
 int /*<<< orphan*/  xfree (int /*<<< orphan*/ *) ; 

void
free_header_files (void)
{
  if (this_object_header_files)
    {
      xfree (this_object_header_files);
      this_object_header_files = NULL;
    }
  n_allocated_this_object_header_files = 0;
}