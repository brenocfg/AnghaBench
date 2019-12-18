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
struct TYPE_2__ {int /*<<< orphan*/ * core_read_registers; } ;

/* Variables and functions */
 scalar_t__ core_gdbarch ; 
 TYPE_1__* core_vec ; 
 int /*<<< orphan*/  deprecated_registers_fetched () ; 
 int /*<<< orphan*/  fprintf_filtered (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  gdb_stderr ; 
 scalar_t__ gdbarch_regset_from_core_section_p (scalar_t__) ; 
 int /*<<< orphan*/  get_core_register_section (char*,int,char*,int) ; 

__attribute__((used)) static void
get_core_registers (int regno)
{
  int status;

  if (!(core_gdbarch && gdbarch_regset_from_core_section_p (core_gdbarch))
      && (core_vec == NULL || core_vec->core_read_registers == NULL))
    {
      fprintf_filtered (gdb_stderr,
		     "Can't fetch registers from this type of core file\n");
      return;
    }

  get_core_register_section (".reg", 0, "general-purpose", 1);
  get_core_register_section (".reg2", 2, "floating-point", 0);
  get_core_register_section (".reg-xfp", 3, "extended floating-point", 0);

  deprecated_registers_fetched ();
}