#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct coff_section_tdata {int dummy; } ;
typedef  int bfd_size_type ;
typedef  int /*<<< orphan*/  bfd_byte ;
typedef  int /*<<< orphan*/  bfd_boolean ;
typedef  int /*<<< orphan*/  bfd ;
struct TYPE_6__ {int /*<<< orphan*/ * used_by_bfd; } ;
typedef  TYPE_1__ asection ;
struct TYPE_7__ {int /*<<< orphan*/ * contents; } ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  bfd_malloc_and_get_section (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/ * bfd_zalloc (int /*<<< orphan*/ *,int) ; 
 TYPE_3__* coff_section_data (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 

__attribute__((used)) static bfd_boolean
xcoff_get_section_contents (bfd *abfd, asection *sec)
{
  if (coff_section_data (abfd, sec) == NULL)
    {
      bfd_size_type amt = sizeof (struct coff_section_tdata);

      sec->used_by_bfd = bfd_zalloc (abfd, amt);
      if (sec->used_by_bfd == NULL)
	return FALSE;
    }

  if (coff_section_data (abfd, sec)->contents == NULL)
    {
      bfd_byte *contents;

      if (! bfd_malloc_and_get_section (abfd, sec, &contents))
	{
	  if (contents != NULL)
	    free (contents);
	  return FALSE;
	}
      coff_section_data (abfd, sec)->contents = contents;
    }

  return TRUE;
}