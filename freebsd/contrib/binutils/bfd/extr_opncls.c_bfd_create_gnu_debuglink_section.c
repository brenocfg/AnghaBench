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
typedef  int flagword ;
typedef  int bfd_size_type ;
typedef  int /*<<< orphan*/  bfd ;
typedef  int /*<<< orphan*/  asection ;

/* Variables and functions */
 int /*<<< orphan*/  GNU_DEBUGLINK ; 
 int SEC_DEBUGGING ; 
 int SEC_HAS_CONTENTS ; 
 int SEC_READONLY ; 
 int /*<<< orphan*/  bfd_error_invalid_operation ; 
 int /*<<< orphan*/ * bfd_get_section_by_name (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * bfd_make_section_with_flags (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  bfd_set_error (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfd_set_section_size (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 char* lbasename (char const*) ; 
 int strlen (char const*) ; 

asection *
bfd_create_gnu_debuglink_section (bfd *abfd, const char *filename)
{
  asection *sect;
  bfd_size_type debuglink_size;
  flagword flags;

  if (abfd == NULL || filename == NULL)
    {
      bfd_set_error (bfd_error_invalid_operation);
      return NULL;
    }

  /* Strip off any path components in filename.  */
  filename = lbasename (filename);

  sect = bfd_get_section_by_name (abfd, GNU_DEBUGLINK);
  if (sect)
    {
      /* Section already exists.  */
      bfd_set_error (bfd_error_invalid_operation);
      return NULL;
    }

  flags = SEC_HAS_CONTENTS | SEC_READONLY | SEC_DEBUGGING;
  sect = bfd_make_section_with_flags (abfd, GNU_DEBUGLINK, flags);
  if (sect == NULL)
    return NULL;

  debuglink_size = strlen (filename) + 1;
  debuglink_size += 3;
  debuglink_size &= ~3;
  debuglink_size += 4;

  if (! bfd_set_section_size (abfd, sect, debuglink_size))
    /* XXX Should we delete the section from the bfd ?  */
    return NULL;

  return sect;
}