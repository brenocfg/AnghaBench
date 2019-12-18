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
typedef  int /*<<< orphan*/  bfd_size_type ;
typedef  int /*<<< orphan*/  bfd_byte ;
typedef  int /*<<< orphan*/  bfd_boolean ;
typedef  int /*<<< orphan*/  bfd ;
typedef  int /*<<< orphan*/  asection ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/ * bfd_get_section_by_name (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  bfd_get_section_contents (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfd_section_size (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  parse_ieee (void*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ xmalloc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bfd_boolean
read_ieee_debugging_info (bfd *abfd, void *dhandle, bfd_boolean *pfound)
{
  asection *dsec;
  bfd_size_type size;
  bfd_byte *contents;

  /* The BFD backend puts the debugging information into a section
     named .debug.  */

  dsec = bfd_get_section_by_name (abfd, ".debug");
  if (dsec == NULL)
    return TRUE;

  size = bfd_section_size (abfd, dsec);
  contents = (bfd_byte *) xmalloc (size);
  if (! bfd_get_section_contents (abfd, dsec, contents, 0, size))
    return FALSE;

  if (! parse_ieee (dhandle, abfd, contents, size))
    return FALSE;

  free (contents);

  *pfound = TRUE;

  return TRUE;
}