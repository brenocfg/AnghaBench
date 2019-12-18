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
typedef  int /*<<< orphan*/  symbolS ;
struct elf_obj_sy {int /*<<< orphan*/ * versioned_name; int /*<<< orphan*/ * size; } ;

/* Variables and functions */
 scalar_t__ ECOFF_DEBUGGING ; 
 int /*<<< orphan*/  ecoff_symbol_new_hook (int /*<<< orphan*/ *) ; 
 struct elf_obj_sy* symbol_get_obj (int /*<<< orphan*/ *) ; 

void
elf_obj_symbol_new_hook (symbolS *symbolP)
{
  struct elf_obj_sy *sy_obj;

  sy_obj = symbol_get_obj (symbolP);
  sy_obj->size = NULL;
  sy_obj->versioned_name = NULL;

#ifdef NEED_ECOFF_DEBUG
  if (ECOFF_DEBUGGING)
    ecoff_symbol_new_hook (symbolP);
#endif
}