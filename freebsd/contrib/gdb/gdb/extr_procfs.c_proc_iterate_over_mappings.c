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
typedef  int /*<<< orphan*/  procinfo ;

/* Variables and functions */
 int /*<<< orphan*/  PIDGET (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * find_procinfo_or_die (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  inferior_ptid ; 
 int iterate_over_mappings (int /*<<< orphan*/ *,int (*) (int,CORE_ADDR),int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  solib_mappings_callback ; 

int
proc_iterate_over_mappings (int (*func) (int, CORE_ADDR))
{
  procinfo *pi = find_procinfo_or_die (PIDGET (inferior_ptid), 0);

  return iterate_over_mappings (pi, func, pi, solib_mappings_callback);
}