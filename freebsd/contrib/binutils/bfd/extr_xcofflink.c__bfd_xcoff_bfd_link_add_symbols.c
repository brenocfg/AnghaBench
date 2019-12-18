#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
struct bfd_link_info {TYPE_1__* hash; } ;
typedef  int /*<<< orphan*/  bfd_boolean ;
struct TYPE_15__ {int flags; int archive_pass; int /*<<< orphan*/  xvec; } ;
typedef  TYPE_2__ bfd ;
struct TYPE_14__ {int /*<<< orphan*/  creator; } ;

/* Variables and functions */
 int DYNAMIC ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  _bfd_generic_link_add_archive_symbols (TYPE_2__*,struct bfd_link_info*,int /*<<< orphan*/  (*) (TYPE_2__*,struct bfd_link_info*,int /*<<< orphan*/ *)) ; 
#define  bfd_archive 129 
 int /*<<< orphan*/  bfd_check_format (TYPE_2__*,int const) ; 
 int /*<<< orphan*/  bfd_error_wrong_format ; 
 int bfd_get_format (TYPE_2__*) ; 
 int /*<<< orphan*/  bfd_has_map (TYPE_2__*) ; 
#define  bfd_object 128 
 TYPE_2__* bfd_openr_next_archived_file (TYPE_2__*,TYPE_2__*) ; 
 int /*<<< orphan*/  bfd_set_error (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xcoff_link_add_object_symbols (TYPE_2__*,struct bfd_link_info*) ; 
 int /*<<< orphan*/  xcoff_link_check_archive_element (TYPE_2__*,struct bfd_link_info*,int /*<<< orphan*/ *) ; 

bfd_boolean
_bfd_xcoff_bfd_link_add_symbols (bfd *abfd, struct bfd_link_info *info)
{
  switch (bfd_get_format (abfd))
    {
    case bfd_object:
      return xcoff_link_add_object_symbols (abfd, info);

    case bfd_archive:
      /* If the archive has a map, do the usual search.  We then need
	 to check the archive for dynamic objects, because they may not
	 appear in the archive map even though they should, perhaps, be
	 included.  If the archive has no map, we just consider each object
	 file in turn, since that apparently is what the AIX native linker
	 does.  */
      if (bfd_has_map (abfd))
	{
	  if (! (_bfd_generic_link_add_archive_symbols
		 (abfd, info, xcoff_link_check_archive_element)))
	    return FALSE;
	}

      {
	bfd *member;

	member = bfd_openr_next_archived_file (abfd, NULL);
	while (member != NULL)
	  {
	    if (bfd_check_format (member, bfd_object)
		&& (info->hash->creator == member->xvec)
		&& (! bfd_has_map (abfd) || (member->flags & DYNAMIC) != 0))
	      {
		bfd_boolean needed;

		if (! xcoff_link_check_archive_element (member, info,
							&needed))
		  return FALSE;
		if (needed)
		  member->archive_pass = -1;
	      }
	    member = bfd_openr_next_archived_file (abfd, member);
	  }
      }

      return TRUE;

    default:
      bfd_set_error (bfd_error_wrong_format);
      return FALSE;
    }
}