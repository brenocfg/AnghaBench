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
struct TYPE_2__ {scalar_t__ e_type; scalar_t__ e_phnum; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 scalar_t__ ET_CORE ; 
 char* _ (char*) ; 
 int /*<<< orphan*/  do_notes ; 
 TYPE_1__ elf_header ; 
 int /*<<< orphan*/  printf (char*) ; 
 int process_corefile_note_segments (int /*<<< orphan*/ *) ; 
 int process_note_sections (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
process_notes (FILE *file)
{
  /* If we have not been asked to display the notes then do nothing.  */
  if (! do_notes)
    return 1;

  if (elf_header.e_type != ET_CORE)
    return process_note_sections (file);

  /* No program headers means no NOTE segment.  */
  if (elf_header.e_phnum > 0)
    return process_corefile_note_segments (file);

  printf (_("No note segments present in the core file.\n"));
  return 1;
}