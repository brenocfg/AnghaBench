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
struct target_ops {int dummy; } ;
struct section_table {TYPE_1__* the_bfd_section; } ;
struct gdbarch {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  name; } ;
typedef  int /*<<< orphan*/  CORE_ADDR ;

/* Variables and functions */
 int /*<<< orphan*/  get_target_memory_unsigned (struct target_ops*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 
 struct section_table* target_section_by_addr (struct target_ops*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static CORE_ADDR
ppc64_fbsd_convert_from_func_ptr_addr (struct gdbarch *gdbarch,
				       CORE_ADDR addr,
				       struct target_ops *targ)
{
  struct section_table *s = target_section_by_addr (targ, addr);
  
  /* Check if ADDR points to a function descriptor.  */
  if (s && strcmp (s->the_bfd_section->name, ".opd") == 0)
    return get_target_memory_unsigned (targ, addr, 8);

  return addr;
}