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
struct objfile {int /*<<< orphan*/  obfd; } ;
typedef  int /*<<< orphan*/  bfd_byte ;
typedef  int /*<<< orphan*/  CORE_ADDR ;

/* Variables and functions */
 int /*<<< orphan*/  DIE_ID ; 
 int /*<<< orphan*/  DIE_NAME ; 
 int /*<<< orphan*/  bfd_get_16 (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bfd_get_32 (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bfd_get_64 (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bfd_get_8 (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  complaint (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  symfile_complaints ; 

__attribute__((used)) static CORE_ADDR
target_to_host (char *from, int nbytes, int signextend,	/* FIXME:  Unused */
		struct objfile *objfile)
{
  CORE_ADDR rtnval;

  switch (nbytes)
    {
    case 8:
      rtnval = bfd_get_64 (objfile->obfd, (bfd_byte *) from);
      break;
    case 4:
      rtnval = bfd_get_32 (objfile->obfd, (bfd_byte *) from);
      break;
    case 2:
      rtnval = bfd_get_16 (objfile->obfd, (bfd_byte *) from);
      break;
    case 1:
      rtnval = bfd_get_8 (objfile->obfd, (bfd_byte *) from);
      break;
    default:
      complaint (&symfile_complaints,
		 "DIE @ 0x%x \"%s\", no bfd support for %d byte data object",
		 DIE_ID, DIE_NAME, nbytes);
      rtnval = 0;
      break;
    }
  return (rtnval);
}