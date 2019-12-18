#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  file_ptr ;
typedef  int /*<<< orphan*/  bfd_target ;
typedef  int /*<<< orphan*/  bfd_size_type ;
typedef  char bfd_byte ;
struct TYPE_9__ {void* any; } ;
struct TYPE_10__ {scalar_t__ symcount; int /*<<< orphan*/  const* xvec; int /*<<< orphan*/  flags; TYPE_1__ tdata; } ;
typedef  TYPE_2__ bfd ;

/* Variables and functions */
 int /*<<< orphan*/  HAS_SYMS ; 
 int /*<<< orphan*/  ISHEX (char) ; 
 int /*<<< orphan*/  SEEK_SET ; 
 int bfd_bread (char*,int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  bfd_error_wrong_format ; 
 int /*<<< orphan*/  bfd_release (TYPE_2__*,void*) ; 
 scalar_t__ bfd_seek (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfd_set_error (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  srec_init () ; 
 int /*<<< orphan*/  srec_mkobject (TYPE_2__*) ; 
 int /*<<< orphan*/  srec_scan (TYPE_2__*) ; 

__attribute__((used)) static const bfd_target *
srec_object_p (bfd *abfd)
{
  void * tdata_save;
  bfd_byte b[4];

  srec_init ();

  if (bfd_seek (abfd, (file_ptr) 0, SEEK_SET) != 0
      || bfd_bread (b, (bfd_size_type) 4, abfd) != 4)
    return NULL;

  if (b[0] != 'S' || !ISHEX (b[1]) || !ISHEX (b[2]) || !ISHEX (b[3]))
    {
      bfd_set_error (bfd_error_wrong_format);
      return NULL;
    }

  tdata_save = abfd->tdata.any;
  if (! srec_mkobject (abfd) || ! srec_scan (abfd))
    {
      if (abfd->tdata.any != tdata_save && abfd->tdata.any != NULL)
	bfd_release (abfd, abfd->tdata.any);
      abfd->tdata.any = tdata_save;
      return NULL;
    }

  if (abfd->symcount > 0)
    abfd->flags |= HAS_SYMS;

  return abfd->xvec;
}