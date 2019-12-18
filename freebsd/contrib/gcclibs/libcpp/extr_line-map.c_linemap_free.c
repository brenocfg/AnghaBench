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
struct line_maps {scalar_t__ maps; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (scalar_t__) ; 
 int /*<<< orphan*/  linemap_check_files_exited (struct line_maps*) ; 

void
linemap_free (struct line_maps *set)
{
  if (set->maps)
    {
      linemap_check_files_exited (set);

      free (set->maps);
    }
}