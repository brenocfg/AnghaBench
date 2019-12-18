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
struct TYPE_10__ {int /*<<< orphan*/  const* xvec; TYPE_1__ tdata; } ;
typedef  TYPE_2__ bfd ;

/* Variables and functions */
 unsigned int HEX2 (char*) ; 
 int /*<<< orphan*/  ISHEX (char) ; 
 int /*<<< orphan*/  SEEK_SET ; 
 int bfd_bread (char*,int /*<<< orphan*/ ,TYPE_2__*) ; 
 scalar_t__ bfd_error_file_truncated ; 
 int /*<<< orphan*/  bfd_error_wrong_format ; 
 scalar_t__ bfd_get_error () ; 
 int /*<<< orphan*/  bfd_release (TYPE_2__*,void*) ; 
 scalar_t__ bfd_seek (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfd_set_error (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ihex_init () ; 
 int /*<<< orphan*/  ihex_mkobject (TYPE_2__*) ; 
 int /*<<< orphan*/  ihex_scan (TYPE_2__*) ; 

__attribute__((used)) static const bfd_target *
ihex_object_p (bfd *abfd)
{
  void * tdata_save;
  bfd_byte b[9];
  unsigned int i;
  unsigned int type;

  ihex_init ();

  if (bfd_seek (abfd, (file_ptr) 0, SEEK_SET) != 0)
    return NULL;
  if (bfd_bread (b, (bfd_size_type) 9, abfd) != 9)
    {
      if (bfd_get_error () == bfd_error_file_truncated)
	bfd_set_error (bfd_error_wrong_format);
      return NULL;
    }

  if (b[0] != ':')
    {
      bfd_set_error (bfd_error_wrong_format);
      return NULL;
    }

  for (i = 1; i < 9; i++)
    {
      if (! ISHEX (b[i]))
	{
	  bfd_set_error (bfd_error_wrong_format);
	  return NULL;
	}
    }

  type = HEX2 (b + 7);
  if (type > 5)
    {
      bfd_set_error (bfd_error_wrong_format);
      return NULL;
    }

  /* OK, it looks like it really is an Intel Hex file.  */
  tdata_save = abfd->tdata.any;
  if (! ihex_mkobject (abfd) || ! ihex_scan (abfd))
    {
      if (abfd->tdata.any != tdata_save && abfd->tdata.any != NULL)
	bfd_release (abfd, abfd->tdata.any);
      abfd->tdata.any = tdata_save;
      return NULL;
    }

  return abfd->xvec;
}