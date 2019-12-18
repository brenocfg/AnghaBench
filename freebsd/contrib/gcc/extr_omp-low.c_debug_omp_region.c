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
struct omp_region {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  dump_omp_region (int /*<<< orphan*/ ,struct omp_region*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stderr ; 

void
debug_omp_region (struct omp_region *region)
{
  dump_omp_region (stderr, region, 0);
}