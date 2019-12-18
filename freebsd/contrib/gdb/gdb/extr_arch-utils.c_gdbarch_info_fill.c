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
struct gdbarch_info {scalar_t__ byte_order; scalar_t__ osabi; int /*<<< orphan*/ * bfd_arch_info; int /*<<< orphan*/ * abfd; } ;
struct gdbarch {int dummy; } ;

/* Variables and functions */
 scalar_t__ BFD_ENDIAN_BIG ; 
 scalar_t__ BFD_ENDIAN_LITTLE ; 
 scalar_t__ BFD_ENDIAN_UNKNOWN ; 
 scalar_t__ GDB_OSABI_UNINITIALIZED ; 
 scalar_t__ bfd_arch_obscure ; 
 scalar_t__ bfd_arch_unknown ; 
 scalar_t__ bfd_big_endian (int /*<<< orphan*/ *) ; 
 scalar_t__ bfd_get_arch (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * bfd_get_arch_info (int /*<<< orphan*/ *) ; 
 scalar_t__ bfd_little_endian (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gdb_assert (int /*<<< orphan*/ ) ; 
 void* gdbarch_bfd_arch_info (struct gdbarch*) ; 
 void* gdbarch_byte_order (struct gdbarch*) ; 
 scalar_t__ gdbarch_lookup_osabi (int /*<<< orphan*/ *) ; 
 scalar_t__ gdbarch_osabi (struct gdbarch*) ; 
 int /*<<< orphan*/  target_architecture_auto ; 
 int /*<<< orphan*/  target_byte_order_auto ; 

void
gdbarch_info_fill (struct gdbarch *gdbarch, struct gdbarch_info *info)
{
  /* "(gdb) set architecture ...".  */
  if (info->bfd_arch_info == NULL
      && !target_architecture_auto
      && gdbarch != NULL)
    info->bfd_arch_info = gdbarch_bfd_arch_info (gdbarch);
  if (info->bfd_arch_info == NULL
      && info->abfd != NULL
      && bfd_get_arch (info->abfd) != bfd_arch_unknown
      && bfd_get_arch (info->abfd) != bfd_arch_obscure)
    info->bfd_arch_info = bfd_get_arch_info (info->abfd);
  if (info->bfd_arch_info == NULL
      && gdbarch != NULL)
    info->bfd_arch_info = gdbarch_bfd_arch_info (gdbarch);

  /* "(gdb) set byte-order ...".  */
  if (info->byte_order == BFD_ENDIAN_UNKNOWN
      && !target_byte_order_auto
      && gdbarch != NULL)
    info->byte_order = gdbarch_byte_order (gdbarch);
  /* From the INFO struct.  */
  if (info->byte_order == BFD_ENDIAN_UNKNOWN
      && info->abfd != NULL)
    info->byte_order = (bfd_big_endian (info->abfd) ? BFD_ENDIAN_BIG
		       : bfd_little_endian (info->abfd) ? BFD_ENDIAN_LITTLE
		       : BFD_ENDIAN_UNKNOWN);
  /* From the current target.  */
  if (info->byte_order == BFD_ENDIAN_UNKNOWN
      && gdbarch != NULL)
    info->byte_order = gdbarch_byte_order (gdbarch);

  /* "(gdb) set osabi ...".  Handled by gdbarch_lookup_osabi.  */
  if (info->osabi == GDB_OSABI_UNINITIALIZED)
    info->osabi = gdbarch_lookup_osabi (info->abfd);
  if (info->osabi == GDB_OSABI_UNINITIALIZED
      && gdbarch != NULL)
    info->osabi = gdbarch_osabi (gdbarch);

  /* Must have at least filled in the architecture.  */
  gdb_assert (info->bfd_arch_info != NULL);
}