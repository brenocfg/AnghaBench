#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {char const* filename; scalar_t__ filesize; } ;
typedef  TYPE_1__ filename_and_size_t ;
typedef  int /*<<< orphan*/  bfd_boolean ;
typedef  int /*<<< orphan*/  bfd ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  bfd_check_format (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfd_close (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bfd_map_over_sections (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  bfd_nonfatal (char const*) ; 
 int /*<<< orphan*/  bfd_object ; 
 int /*<<< orphan*/ * bfd_openr (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  got_a_section ; 
 int /*<<< orphan*/  strings_a_section ; 
 int /*<<< orphan*/  target ; 

__attribute__((used)) static bfd_boolean
strings_object_file (const char *file)
{
  filename_and_size_t filename_and_size;
  bfd *abfd;

  abfd = bfd_openr (file, target);

  if (abfd == NULL)
    /* Treat the file as a non-object file.  */
    return FALSE;

  /* This call is mainly for its side effect of reading in the sections.
     We follow the traditional behavior of `strings' in that we don't
     complain if we don't recognize a file to be an object file.  */
  if (!bfd_check_format (abfd, bfd_object))
    {
      bfd_close (abfd);
      return FALSE;
    }

  got_a_section = FALSE;
  filename_and_size.filename = file;
  filename_and_size.filesize = 0;
  bfd_map_over_sections (abfd, strings_a_section, & filename_and_size);

  if (!bfd_close (abfd))
    {
      bfd_nonfatal (file);
      return FALSE;
    }

  return got_a_section;
}