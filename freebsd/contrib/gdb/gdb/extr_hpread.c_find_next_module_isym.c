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
typedef  int /*<<< orphan*/  quick_module_entry ;
typedef  int /*<<< orphan*/  PXDB_header_ptr ;

/* Variables and functions */
 int CURR_MODULE_ISYM ; 
 scalar_t__ VALID_CURR_MODULE ; 

__attribute__((used)) static int
find_next_module_isym (int index, quick_module_entry *qMD, int curr_md,
		       PXDB_header_ptr pxdb_header_p)
{
  while (VALID_CURR_MODULE)
    {
      if (CURR_MODULE_ISYM >= index)
	return CURR_MODULE_ISYM - 1;
      curr_md++;
    }
  return 0;
}