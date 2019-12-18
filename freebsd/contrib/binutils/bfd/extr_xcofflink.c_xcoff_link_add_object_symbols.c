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
typedef  int /*<<< orphan*/  bfd_boolean ;
typedef  int /*<<< orphan*/  bfd ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  _bfd_coff_free_symbols (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _bfd_coff_get_external_symbols (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xcoff_link_add_symbols (int /*<<< orphan*/ *,struct bfd_link_info*) ; 

__attribute__((used)) static bfd_boolean
xcoff_link_add_object_symbols (bfd *abfd, struct bfd_link_info *info)
{
  if (! _bfd_coff_get_external_symbols (abfd))
    return FALSE;
  if (! xcoff_link_add_symbols (abfd, info))
    return FALSE;
  if (! info->keep_memory)
    {
      if (! _bfd_coff_free_symbols (abfd))
	return FALSE;
    }
  return TRUE;
}