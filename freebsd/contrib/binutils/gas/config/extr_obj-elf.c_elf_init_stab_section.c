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
typedef  int /*<<< orphan*/  segT ;

/* Variables and functions */
 int /*<<< orphan*/  ECOFF_DEBUGGING ; 
 int /*<<< orphan*/  obj_elf_init_stab_section (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
elf_init_stab_section (segT seg)
{
#ifdef NEED_ECOFF_DEBUG
  if (!ECOFF_DEBUGGING)
#endif
    obj_elf_init_stab_section (seg);
}