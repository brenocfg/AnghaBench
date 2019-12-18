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
struct target_ops {struct section_table* to_sections_end; struct section_table* to_sections; } ;
struct section_table {int /*<<< orphan*/ * bfd; TYPE_1__* the_bfd_section; int /*<<< orphan*/  endaddr; int /*<<< orphan*/  addr; } ;
typedef  int /*<<< orphan*/  bfd ;
struct TYPE_2__ {int /*<<< orphan*/  filepos; } ;

/* Variables and functions */
 int TARGET_ADDR_BIT ; 
 int /*<<< orphan*/  bfd_get_filename (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bfd_get_start_address (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bfd_get_target (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bfd_section_name (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/ * exec_bfd ; 
 int /*<<< orphan*/  gdb_stdout ; 
 scalar_t__ info_verbose ; 
 int /*<<< orphan*/  local_hex_string_custom (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  print_address_numeric (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf_filtered (char*,...) ; 
 int /*<<< orphan*/  wrap_here (char*) ; 

void
print_section_info (struct target_ops *t, bfd *abfd)
{
  struct section_table *p;
  /* FIXME: "016l" is not wide enough when TARGET_ADDR_BIT > 64.  */
  char *fmt = TARGET_ADDR_BIT <= 32 ? "08l" : "016l";

  printf_filtered ("\t`%s', ", bfd_get_filename (abfd));
  wrap_here ("        ");
  printf_filtered ("file type %s.\n", bfd_get_target (abfd));
  if (abfd == exec_bfd)
    {
      printf_filtered ("\tEntry point: ");
      print_address_numeric (bfd_get_start_address (abfd), 1, gdb_stdout);
      printf_filtered ("\n");
    }
  for (p = t->to_sections; p < t->to_sections_end; p++)
    {
      printf_filtered ("\t%s", local_hex_string_custom (p->addr, fmt));
      printf_filtered (" - %s", local_hex_string_custom (p->endaddr, fmt));

      /* FIXME: A format of "08l" is not wide enough for file offsets
	 larger than 4GB.  OTOH, making it "016l" isn't desirable either
	 since most output will then be much wider than necessary.  It
	 may make sense to test the size of the file and choose the
	 format string accordingly.  */
      if (info_verbose)
	printf_filtered (" @ %s",
			 local_hex_string_custom (p->the_bfd_section->filepos, "08l"));
      printf_filtered (" is %s", bfd_section_name (p->bfd, p->the_bfd_section));
      if (p->bfd != abfd)
	{
	  printf_filtered (" in %s", bfd_get_filename (p->bfd));
	}
      printf_filtered ("\n");
    }
}