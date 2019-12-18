#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ bfd_size_type ;
typedef  int /*<<< orphan*/  bfd_byte ;
typedef  int /*<<< orphan*/  bfd ;
struct TYPE_6__ {scalar_t__ size; } ;
typedef  TYPE_1__ asection ;
struct TYPE_7__ {unsigned int mach; int /*<<< orphan*/  string; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_4__*) ; 
 int /*<<< orphan*/  NOTE_ARCH_STRING ; 
 TYPE_4__* architectures ; 
 int /*<<< orphan*/  arm_check_note (int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ,char**) ; 
 TYPE_1__* bfd_get_section_by_name (int /*<<< orphan*/ *,char const*) ; 
 unsigned int bfd_mach_arm_unknown ; 
 int /*<<< orphan*/  bfd_malloc_and_get_section (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 scalar_t__ strcmp (char*,int /*<<< orphan*/ ) ; 

unsigned int
bfd_arm_get_mach_from_notes (bfd *abfd, const char *note_section)
{
  asection *     arm_arch_section;
  bfd_size_type  buffer_size;
  bfd_byte *     buffer;
  char *         arch_string;
  int            i;

  /* Look for a note section.  If one is present check the architecture
     string encoded in it, and set it to the current architecture if it is
     different.  */
  arm_arch_section = bfd_get_section_by_name (abfd, note_section);

  if (arm_arch_section == NULL)
    return bfd_mach_arm_unknown;

  buffer_size = arm_arch_section->size;
  if (buffer_size == 0)
    return bfd_mach_arm_unknown;

  if (!bfd_malloc_and_get_section (abfd, arm_arch_section, &buffer))
    goto FAIL;

  /* Parse the note.  */
  if (! arm_check_note (abfd, buffer, buffer_size, NOTE_ARCH_STRING, & arch_string))
    goto FAIL;

  /* Interpret the architecture string.  */
  for (i = ARRAY_SIZE (architectures); i--;)
    if (strcmp (arch_string, architectures[i].string) == 0)
      {
	free (buffer);
	return architectures[i].mach;
      }

 FAIL:
  if (buffer != NULL)
    free (buffer);
  return bfd_mach_arm_unknown;
}