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
struct omp_region {int type; struct omp_region* next; struct omp_region* inner; } ;

/* Variables and functions */
#define  OMP_CRITICAL 135 
#define  OMP_FOR 134 
#define  OMP_MASTER 133 
#define  OMP_ORDERED 132 
#define  OMP_PARALLEL 131 
#define  OMP_SECTION 130 
#define  OMP_SECTIONS 129 
#define  OMP_SINGLE 128 
 int /*<<< orphan*/  expand_omp_for (struct omp_region*) ; 
 int /*<<< orphan*/  expand_omp_parallel (struct omp_region*) ; 
 int /*<<< orphan*/  expand_omp_sections (struct omp_region*) ; 
 int /*<<< orphan*/  expand_omp_single (struct omp_region*) ; 
 int /*<<< orphan*/  expand_omp_synch (struct omp_region*) ; 
 int /*<<< orphan*/  gcc_unreachable () ; 

__attribute__((used)) static void
expand_omp (struct omp_region *region)
{
  while (region)
    {
      if (region->inner)
	expand_omp (region->inner);

      switch (region->type)
	{
	case OMP_PARALLEL:
	  expand_omp_parallel (region);
	  break;

	case OMP_FOR:
	  expand_omp_for (region);
	  break;

	case OMP_SECTIONS:
	  expand_omp_sections (region);
	  break;

	case OMP_SECTION:
	  /* Individual omp sections are handled together with their
	     parent OMP_SECTIONS region.  */
	  break;

	case OMP_SINGLE:
	  expand_omp_single (region);
	  break;

	case OMP_MASTER:
	case OMP_ORDERED:
	case OMP_CRITICAL:
	  expand_omp_synch (region);
	  break;

	default:
	  gcc_unreachable ();
	}

      region = region->next;
    }
}