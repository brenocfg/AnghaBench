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
 int depth_reached ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  print_class_statistics () ; 
 int /*<<< orphan*/  print_search_statistics () ; 
 int /*<<< orphan*/  stderr ; 

void
cxx_print_statistics (void)
{
  print_search_statistics ();
  print_class_statistics ();
#ifdef GATHER_STATISTICS
  fprintf (stderr, "maximum template instantiation depth reached: %d\n",
	   depth_reached);
#endif
}