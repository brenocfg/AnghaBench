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
 int /*<<< orphan*/  elf_common_parse ; 
 scalar_t__ flag_mri ; 
 int /*<<< orphan*/  s_comm_internal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  s_mri_common (int /*<<< orphan*/ ) ; 

void
obj_elf_common (int is_common)
{
  if (flag_mri && is_common)
    s_mri_common (0);
  else
    s_comm_internal (0, elf_common_parse);
}