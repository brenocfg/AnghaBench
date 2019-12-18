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
struct bfd_link_info {int /*<<< orphan*/  keep_memory; } ;
typedef  scalar_t__ bfd_boolean ;
typedef  int /*<<< orphan*/  bfd ;

/* Variables and functions */
 scalar_t__ FALSE ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  _bfd_coff_free_symbols (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _bfd_coff_get_external_symbols (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  coff_link_add_symbols (int /*<<< orphan*/ *,struct bfd_link_info*) ; 
 int /*<<< orphan*/  coff_link_check_ar_symbols (int /*<<< orphan*/ *,struct bfd_link_info*,scalar_t__*) ; 

__attribute__((used)) static bfd_boolean
coff_link_check_archive_element (bfd *abfd,
				 struct bfd_link_info *info,
				 bfd_boolean *pneeded)
{
  if (! _bfd_coff_get_external_symbols (abfd))
    return FALSE;

  if (! coff_link_check_ar_symbols (abfd, info, pneeded))
    return FALSE;

  if (*pneeded
      && ! coff_link_add_symbols (abfd, info))
    return FALSE;

  if ((! info->keep_memory || ! *pneeded)
      && ! _bfd_coff_free_symbols (abfd))
    return FALSE;

  return TRUE;
}