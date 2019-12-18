#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  file_ptr ;
typedef  scalar_t__ bfd_size_type ;
typedef  int /*<<< orphan*/  bfd_byte ;
typedef  int /*<<< orphan*/  bfd_boolean ;
typedef  int /*<<< orphan*/  bfd ;
struct TYPE_5__ {scalar_t__ size; } ;
typedef  TYPE_1__ asection ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  NOTE_ARCH_STRING ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  _bfd_error_handler (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  arm_Note ; 
 int /*<<< orphan*/  arm_check_note (int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ,char**) ; 
 int /*<<< orphan*/  bfd_get_filename (int /*<<< orphan*/ *) ; 
 int bfd_get_mach (int /*<<< orphan*/ *) ; 
 TYPE_1__* bfd_get_section_by_name (int /*<<< orphan*/ *,char const*) ; 
#define  bfd_mach_arm_2 141 
#define  bfd_mach_arm_2a 140 
#define  bfd_mach_arm_3 139 
#define  bfd_mach_arm_3M 138 
#define  bfd_mach_arm_4 137 
#define  bfd_mach_arm_4T 136 
#define  bfd_mach_arm_5 135 
#define  bfd_mach_arm_5T 134 
#define  bfd_mach_arm_5TE 133 
#define  bfd_mach_arm_XScale 132 
#define  bfd_mach_arm_ep9312 131 
#define  bfd_mach_arm_iWMMXt 130 
#define  bfd_mach_arm_iWMMXt2 129 
#define  bfd_mach_arm_unknown 128 
 int /*<<< orphan*/  bfd_malloc_and_get_section (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  bfd_set_section_contents (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  name ; 
 int offsetof (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ strcmp (char*,char*) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 int strlen (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ) ; 

bfd_boolean
bfd_arm_update_notes (bfd *abfd, const char *note_section)
{
  asection *     arm_arch_section;
  bfd_size_type  buffer_size;
  bfd_byte *     buffer;
  char *         arch_string;
  char *         expected;

  /* Look for a note section.  If one is present check the architecture
     string encoded in it, and set it to the current architecture if it is
     different.  */
  arm_arch_section = bfd_get_section_by_name (abfd, note_section);

  if (arm_arch_section == NULL)
    return TRUE;

  buffer_size = arm_arch_section->size;
  if (buffer_size == 0)
    return FALSE;

  if (!bfd_malloc_and_get_section (abfd, arm_arch_section, &buffer))
    goto FAIL;

  /* Parse the note.  */
  if (! arm_check_note (abfd, buffer, buffer_size, NOTE_ARCH_STRING, & arch_string))
    goto FAIL;

  /* Check the architecture in the note against the architecture of the bfd.  */
  switch (bfd_get_mach (abfd))
    {
    default:
    case bfd_mach_arm_unknown: expected = "unknown"; break;
    case bfd_mach_arm_2:       expected = "armv2"; break;
    case bfd_mach_arm_2a:      expected = "armv2a"; break;
    case bfd_mach_arm_3:       expected = "armv3"; break;
    case bfd_mach_arm_3M:      expected = "armv3M"; break;
    case bfd_mach_arm_4:       expected = "armv4"; break;
    case bfd_mach_arm_4T:      expected = "armv4t"; break;
    case bfd_mach_arm_5:       expected = "armv5"; break;
    case bfd_mach_arm_5T:      expected = "armv5t"; break;
    case bfd_mach_arm_5TE:     expected = "armv5te"; break;
    case bfd_mach_arm_XScale:  expected = "XScale"; break;
    case bfd_mach_arm_ep9312:  expected = "ep9312"; break;
    case bfd_mach_arm_iWMMXt:  expected = "iWMMXt"; break;
    case bfd_mach_arm_iWMMXt2: expected = "iWMMXt2"; break;
    }

  if (strcmp (arch_string, expected) != 0)
    {
      strcpy ((char *) buffer + (offsetof (arm_Note, name)
				 + ((strlen (NOTE_ARCH_STRING) + 3) & ~3)),
	      expected);

      if (! bfd_set_section_contents (abfd, arm_arch_section, buffer,
				      (file_ptr) 0, buffer_size))
	{
	  (*_bfd_error_handler)
	    (_("warning: unable to update contents of %s section in %s"),
	     note_section, bfd_get_filename (abfd));
	  goto FAIL;
	}
    }

  free (buffer);
  return TRUE;

 FAIL:
  if (buffer != NULL)
    free (buffer);
  return FALSE;
}