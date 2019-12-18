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
struct areltdata {int /*<<< orphan*/  filename; struct areltdata* arelt_data; scalar_t__ origin; struct areltdata* my_archive; } ;
typedef  int /*<<< orphan*/  file_ptr ;
typedef  struct areltdata bfd ;

/* Variables and functions */
 int /*<<< orphan*/  SEEK_SET ; 
 scalar_t__ _bfd_add_bfd_to_archive_cache (struct areltdata*,int /*<<< orphan*/ ,struct areltdata*) ; 
 struct areltdata* _bfd_create_empty_archive_element_shell (struct areltdata*) ; 
 struct areltdata* _bfd_look_for_bfd_in_cache (struct areltdata*,int /*<<< orphan*/ ) ; 
 struct areltdata* _bfd_read_ar_hdr (struct areltdata*) ; 
 int /*<<< orphan*/  bfd_release (struct areltdata*,struct areltdata*) ; 
 scalar_t__ bfd_seek (struct areltdata*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ bfd_tell (struct areltdata*) ; 

bfd *
_bfd_get_elt_at_filepos (bfd *archive, file_ptr filepos)
{
  struct areltdata *new_areldata;
  bfd *n_nfd;

  if (archive->my_archive)
    {
      filepos += archive->origin;
      archive = archive->my_archive;
    }

  n_nfd = _bfd_look_for_bfd_in_cache (archive, filepos);
  if (n_nfd)
    return n_nfd;

  if (0 > bfd_seek (archive, filepos, SEEK_SET))
    return NULL;

  if ((new_areldata = _bfd_read_ar_hdr (archive)) == NULL)
    return NULL;

  n_nfd = _bfd_create_empty_archive_element_shell (archive);
  if (n_nfd == NULL)
    {
      bfd_release (archive, new_areldata);
      return NULL;
    }

  n_nfd->origin = bfd_tell (archive);
  n_nfd->arelt_data = new_areldata;
  n_nfd->filename = new_areldata->filename;

  if (_bfd_add_bfd_to_archive_cache (archive, filepos, n_nfd))
    return n_nfd;

  /* Huh?  */
  bfd_release (archive, n_nfd);
  bfd_release (archive, new_areldata);
  return NULL;
}