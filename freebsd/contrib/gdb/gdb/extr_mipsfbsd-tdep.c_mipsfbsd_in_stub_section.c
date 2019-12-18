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
struct obj_section {TYPE_1__* the_bfd_section; } ;
struct TYPE_2__ {int /*<<< orphan*/ * name; } ;
typedef  int /*<<< orphan*/  CORE_ADDR ;

/* Variables and functions */
 struct obj_section* find_pc_section (int /*<<< orphan*/ ) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ *,char*) ; 

int 
mipsfbsd_in_stub_section (CORE_ADDR pc, char *name)
{
  struct obj_section *s;
  int retval = 0;

  s = find_pc_section (pc);

  retval = (s != NULL
            && s->the_bfd_section->name != NULL
            && strcmp (s->the_bfd_section->name, ".MIPS.stubs") == 0);
  return (retval);
}