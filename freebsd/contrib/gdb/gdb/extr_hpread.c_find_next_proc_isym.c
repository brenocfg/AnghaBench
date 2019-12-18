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
typedef  int /*<<< orphan*/  quick_procedure_entry ;
typedef  int /*<<< orphan*/  PXDB_header_ptr ;

/* Variables and functions */
 int CURR_PROC_ISYM ; 
 scalar_t__ VALID_CURR_PROC ; 

__attribute__((used)) static int
find_next_proc_isym (int index, quick_procedure_entry *qPD, int curr_pd,
		     PXDB_header_ptr pxdb_header_p)
{
  while (VALID_CURR_PROC)
    {
      if (CURR_PROC_ISYM >= index)
	return CURR_PROC_ISYM - 1;
      curr_pd++;
    }
  return 0;
}