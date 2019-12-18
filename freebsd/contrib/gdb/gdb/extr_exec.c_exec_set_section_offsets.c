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
struct section_table {int /*<<< orphan*/  endaddr; int /*<<< orphan*/  addr; int /*<<< orphan*/  the_bfd_section; } ;
typedef  int flagword ;
typedef  scalar_t__ bfd_signed_vma ;
struct TYPE_2__ {struct section_table* to_sections_end; struct section_table* to_sections; } ;

/* Variables and functions */
 int SEC_ALLOC ; 
 int SEC_CODE ; 
 int SEC_DATA ; 
 int SEC_LOAD ; 
 int bfd_get_section_flags (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  exec_bfd ; 
 TYPE_1__ exec_ops ; 

void
exec_set_section_offsets (bfd_signed_vma text_off, bfd_signed_vma data_off,
			  bfd_signed_vma bss_off)
{
  struct section_table *sect;

  for (sect = exec_ops.to_sections;
       sect < exec_ops.to_sections_end;
       sect++)
    {
      flagword flags;

      flags = bfd_get_section_flags (exec_bfd, sect->the_bfd_section);

      if (flags & SEC_CODE)
	{
	  sect->addr += text_off;
	  sect->endaddr += text_off;
	}
      else if (flags & (SEC_DATA | SEC_LOAD))
	{
	  sect->addr += data_off;
	  sect->endaddr += data_off;
	}
      else if (flags & SEC_ALLOC)
	{
	  sect->addr += bss_off;
	  sect->endaddr += bss_off;
	}
    }
}