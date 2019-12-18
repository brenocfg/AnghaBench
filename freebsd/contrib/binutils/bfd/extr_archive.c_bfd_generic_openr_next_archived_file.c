#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int file_ptr ;
struct TYPE_10__ {int origin; scalar_t__ my_archive; } ;
typedef  TYPE_1__ bfd ;
struct TYPE_11__ {int first_file_filepos; } ;

/* Variables and functions */
 TYPE_1__* _bfd_get_elt_at_filepos (TYPE_1__*,int) ; 
 unsigned int arelt_size (TYPE_1__*) ; 
 TYPE_5__* bfd_ardata (TYPE_1__*) ; 

bfd *
bfd_generic_openr_next_archived_file (bfd *archive, bfd *last_file)
{
  file_ptr filestart;

  if (!last_file)
    filestart = bfd_ardata (archive)->first_file_filepos;
  else
    {
      unsigned int size = arelt_size (last_file);
      filestart = last_file->origin + size;
      if (archive->my_archive)
	filestart -= archive->origin;
      /* Pad to an even boundary...
	 Note that last_file->origin can be odd in the case of
	 BSD-4.4-style element with a long odd size.  */
      filestart += filestart % 2;
    }

  return _bfd_get_elt_at_filepos (archive, filestart);
}