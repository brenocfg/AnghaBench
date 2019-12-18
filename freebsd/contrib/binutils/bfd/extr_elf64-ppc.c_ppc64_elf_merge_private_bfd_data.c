#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  bfd_boolean ;
struct TYPE_9__ {TYPE_1__* xvec; } ;
typedef  TYPE_2__ bfd ;
struct TYPE_8__ {scalar_t__ byteorder; } ;

/* Variables and functions */
 scalar_t__ BFD_ENDIAN_UNKNOWN ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 char* _ (char*) ; 
 int /*<<< orphan*/  _bfd_error_handler (char const*,TYPE_2__*) ; 
 scalar_t__ bfd_big_endian (TYPE_2__*) ; 
 int /*<<< orphan*/  bfd_error_wrong_format ; 
 int /*<<< orphan*/  bfd_set_error (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (char const*,TYPE_2__*) ; 

__attribute__((used)) static bfd_boolean
ppc64_elf_merge_private_bfd_data (bfd *ibfd, bfd *obfd)
{
  /* Check if we have the same endianess.  */
  if (ibfd->xvec->byteorder != obfd->xvec->byteorder
      && ibfd->xvec->byteorder != BFD_ENDIAN_UNKNOWN
      && obfd->xvec->byteorder != BFD_ENDIAN_UNKNOWN)
    {
      const char *msg;

      if (bfd_big_endian (ibfd))
	msg = _("%B: compiled for a big endian system "
		"and target is little endian");
      else
	msg = _("%B: compiled for a little endian system "
		"and target is big endian");

      (*_bfd_error_handler) (msg, ibfd);

      bfd_set_error (bfd_error_wrong_format);
      return FALSE;
    }

  return TRUE;
}