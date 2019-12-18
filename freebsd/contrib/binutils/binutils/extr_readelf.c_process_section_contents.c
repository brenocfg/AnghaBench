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
struct TYPE_2__ {unsigned int e_shnum; } ;
typedef  int /*<<< orphan*/  FILE ;
typedef  int /*<<< orphan*/  Elf_Internal_Shdr ;

/* Variables and functions */
 int DEBUG_DUMP ; 
 int DISASS_DUMP ; 
 int HEX_DUMP ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  disassemble_section (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  display_debug_section (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  do_dump ; 
 int /*<<< orphan*/  dump_section (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int* dump_sects ; 
 TYPE_1__ elf_header ; 
 int /*<<< orphan*/  initialise_dumps_byname () ; 
 unsigned int num_dump_sects ; 
 int /*<<< orphan*/ * section_headers ; 
 int /*<<< orphan*/  warn (int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static void
process_section_contents (FILE *file)
{
  Elf_Internal_Shdr *section;
  unsigned int i;

  if (! do_dump)
    return;

  initialise_dumps_byname ();

  for (i = 0, section = section_headers;
       i < elf_header.e_shnum && i < num_dump_sects;
       i++, section++)
    {
#ifdef SUPPORT_DISASSEMBLY
      if (dump_sects[i] & DISASS_DUMP)
	disassemble_section (section, file);
#endif
      if (dump_sects[i] & HEX_DUMP)
	dump_section (section, file);

      if (dump_sects[i] & DEBUG_DUMP)
	display_debug_section (section, file);
    }

  /* Check to see if the user requested a
     dump of a section that does not exist.  */
  while (i++ < num_dump_sects)
    if (dump_sects[i])
      warn (_("Section %d was not dumped because it does not exist!\n"), i);
}