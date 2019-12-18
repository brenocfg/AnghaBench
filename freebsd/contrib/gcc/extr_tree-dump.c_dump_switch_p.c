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
 size_t TDI_end ; 
 int TDI_none ; 
 int /*<<< orphan*/ * dump_files ; 
 int dump_switch_p_1 (char const*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * extra_dump_files ; 
 size_t extra_dump_files_in_use ; 

int
dump_switch_p (const char *arg)
{
  size_t i;
  int any = 0;

  for (i = TDI_none + 1; i != TDI_end; i++)
    any |= dump_switch_p_1 (arg, &dump_files[i], false);

  /* Don't glob if we got a hit already */
  if (!any)
    for (i = TDI_none + 1; i != TDI_end; i++)
      any |= dump_switch_p_1 (arg, &dump_files[i], true);

  for (i = 0; i < extra_dump_files_in_use; i++)
    any |= dump_switch_p_1 (arg, &extra_dump_files[i], false);
  
  if (!any)
    for (i = 0; i < extra_dump_files_in_use; i++)
      any |= dump_switch_p_1 (arg, &extra_dump_files[i], true);


  return any;
}