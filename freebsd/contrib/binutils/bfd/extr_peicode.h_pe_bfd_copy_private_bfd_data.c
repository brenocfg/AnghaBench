#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  bfd_boolean ;
typedef  int /*<<< orphan*/  bfd ;
struct TYPE_2__ {int real_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int IMAGE_FILE_LARGE_ADDRESS_AWARE ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  _bfd_XX_bfd_copy_private_bfd_data_common (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_1__* pe_data (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pe_saved_coff_bfd_copy_private_bfd_data (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static bfd_boolean
pe_bfd_copy_private_bfd_data (bfd *ibfd, bfd *obfd)
{
  /* PR binutils/716: Copy the large address aware flag.
     XXX: Should we be copying other flags or other fields in the pe_data()
     structure ?  */
  if (pe_data (obfd) != NULL
      && pe_data (ibfd) != NULL
      && pe_data (ibfd)->real_flags & IMAGE_FILE_LARGE_ADDRESS_AWARE)
    pe_data (obfd)->real_flags |= IMAGE_FILE_LARGE_ADDRESS_AWARE;
      
  if (!_bfd_XX_bfd_copy_private_bfd_data_common (ibfd, obfd))
    return FALSE;

  if (pe_saved_coff_bfd_copy_private_bfd_data)
    return pe_saved_coff_bfd_copy_private_bfd_data (ibfd, obfd);

  return TRUE;
}