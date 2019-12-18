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
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int,...) ; 
 int n_compute_conversion_costs ; 
 int n_convert_harshness ; 
 int n_vtable_elems ; 
 int n_vtable_entries ; 
 int n_vtable_searches ; 
 int n_vtables ; 
 int /*<<< orphan*/  stderr ; 

void
print_class_statistics (void)
{
#ifdef GATHER_STATISTICS
  fprintf (stderr, "convert_harshness = %d\n", n_convert_harshness);
  fprintf (stderr, "compute_conversion_costs = %d\n", n_compute_conversion_costs);
  if (n_vtables)
    {
      fprintf (stderr, "vtables = %d; vtable searches = %d\n",
	       n_vtables, n_vtable_searches);
      fprintf (stderr, "vtable entries = %d; vtable elems = %d\n",
	       n_vtable_entries, n_vtable_elems);
    }
#endif
}