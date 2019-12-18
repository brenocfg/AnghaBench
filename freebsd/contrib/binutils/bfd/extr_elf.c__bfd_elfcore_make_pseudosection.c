#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ufile_ptr ;
typedef  int /*<<< orphan*/  bfd_boolean ;
typedef  int /*<<< orphan*/  bfd ;
struct TYPE_4__ {size_t size; int alignment_power; int /*<<< orphan*/  filepos; } ;
typedef  TYPE_1__ asection ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  SEC_HAS_CONTENTS ; 
 char* bfd_alloc (int /*<<< orphan*/ *,size_t) ; 
 TYPE_1__* bfd_make_section_anyway_with_flags (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int elfcore_make_pid (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  elfcore_maybe_make_sect (int /*<<< orphan*/ *,char*,TYPE_1__*) ; 
 int /*<<< orphan*/  memcpy (char*,char*,size_t) ; 
 int /*<<< orphan*/  sprintf (char*,char*,char*,int) ; 
 int strlen (char*) ; 

bfd_boolean
_bfd_elfcore_make_pseudosection (bfd *abfd,
				 char *name,
				 size_t size,
				 ufile_ptr filepos)
{
  char buf[100];
  char *threaded_name;
  size_t len;
  asection *sect;

  /* Build the section name.  */

  sprintf (buf, "%s/%d", name, elfcore_make_pid (abfd));
  len = strlen (buf) + 1;
  threaded_name = bfd_alloc (abfd, len);
  if (threaded_name == NULL)
    return FALSE;
  memcpy (threaded_name, buf, len);

  sect = bfd_make_section_anyway_with_flags (abfd, threaded_name,
					     SEC_HAS_CONTENTS);
  if (sect == NULL)
    return FALSE;
  sect->size = size;
  sect->filepos = filepos;
  sect->alignment_power = 2;

  return elfcore_maybe_make_sect (abfd, name, sect);
}