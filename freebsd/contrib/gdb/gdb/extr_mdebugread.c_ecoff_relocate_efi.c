#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct symbol {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  adr; } ;
struct mips_extra_func_info {TYPE_1__ pdr; } ;
typedef  scalar_t__ CORE_ADDR ;

/* Variables and functions */
 scalar_t__ SYMBOL_VALUE (struct symbol*) ; 

void
ecoff_relocate_efi (struct symbol *sym, CORE_ADDR delta)
{
  struct mips_extra_func_info *e;

  e = (struct mips_extra_func_info *) SYMBOL_VALUE (sym);

  e->pdr.adr += delta;
}