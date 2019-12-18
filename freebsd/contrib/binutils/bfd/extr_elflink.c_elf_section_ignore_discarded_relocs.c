#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct elf_backend_data {scalar_t__ (* elf_backend_ignore_discarded_relocs ) (TYPE_1__*) ;} ;
typedef  int /*<<< orphan*/  bfd_boolean ;
struct TYPE_4__ {int sec_info_type; int /*<<< orphan*/  owner; } ;
typedef  TYPE_1__ asection ;

/* Variables and functions */
#define  ELF_INFO_TYPE_EH_FRAME 129 
#define  ELF_INFO_TYPE_STABS 128 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 struct elf_backend_data* get_elf_backend_data (int /*<<< orphan*/ ) ; 
 scalar_t__ stub1 (TYPE_1__*) ; 

__attribute__((used)) static bfd_boolean
elf_section_ignore_discarded_relocs (asection *sec)
{
  const struct elf_backend_data *bed;

  switch (sec->sec_info_type)
    {
    case ELF_INFO_TYPE_STABS:
    case ELF_INFO_TYPE_EH_FRAME:
      return TRUE;
    default:
      break;
    }

  bed = get_elf_backend_data (sec->owner);
  if (bed->elf_backend_ignore_discarded_relocs != NULL
      && (*bed->elf_backend_ignore_discarded_relocs) (sec))
    return TRUE;

  return FALSE;
}