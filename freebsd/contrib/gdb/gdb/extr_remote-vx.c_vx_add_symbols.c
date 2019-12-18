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
struct section_offsets {void** offsets; } ;
struct objfile {int /*<<< orphan*/  obfd; int /*<<< orphan*/  num_sections; int /*<<< orphan*/  section_offsets; } ;
struct find_sect_args {void* text_start; void* data_start; void* bss_start; } ;
typedef  void* CORE_ADDR ;

/* Variables and functions */
 size_t SECT_OFF_BSS (struct objfile*) ; 
 size_t SECT_OFF_DATA (struct objfile*) ; 
 size_t SECT_OFF_TEXT (struct objfile*) ; 
 int /*<<< orphan*/  SIZEOF_N_SECTION_OFFSETS (int /*<<< orphan*/ ) ; 
 scalar_t__ alloca (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfd_map_over_sections (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct find_sect_args*) ; 
 int /*<<< orphan*/  find_sect ; 
 int /*<<< orphan*/  memcpy (struct section_offsets*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  objfile_relocate (struct objfile*,struct section_offsets*) ; 
 int /*<<< orphan*/  objfile_to_front (struct objfile*) ; 
 struct objfile* symbol_file_add (char*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
vx_add_symbols (char *name, int from_tty, CORE_ADDR text_addr,
		CORE_ADDR data_addr, CORE_ADDR bss_addr)
{
  struct section_offsets *offs;
  struct objfile *objfile;
  struct find_sect_args ss;

  /* It might be nice to suppress the breakpoint_re_set which happens here
     because we are going to do one again after the objfile_relocate.  */
  objfile = symbol_file_add (name, from_tty, NULL, 0, 0);

  /* This is a (slightly cheesy) way of superceding the old symbols.  A less
     cheesy way would be to find the objfile with the same name and
     free_objfile it.  */
  objfile_to_front (objfile);

  offs =
    (struct section_offsets *)
    alloca (SIZEOF_N_SECTION_OFFSETS (objfile->num_sections));
  memcpy (offs, objfile->section_offsets,
          SIZEOF_N_SECTION_OFFSETS (objfile->num_sections));

  ss.text_start = 0;
  ss.data_start = 0;
  ss.bss_start = 0;
  bfd_map_over_sections (objfile->obfd, find_sect, &ss);

  /* Both COFF and b.out frontends use these SECT_OFF_* values.  */
  offs->offsets[SECT_OFF_TEXT (objfile)]  = text_addr - ss.text_start;
  offs->offsets[SECT_OFF_DATA (objfile)] = data_addr - ss.data_start;
  offs->offsets[SECT_OFF_BSS (objfile)] = bss_addr - ss.bss_start;
  objfile_relocate (objfile, offs);
}