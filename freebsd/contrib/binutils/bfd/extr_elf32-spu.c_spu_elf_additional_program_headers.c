#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct spu_link_hash_table {int num_overlays; } ;
struct bfd_link_info {int dummy; } ;
typedef  int /*<<< orphan*/  bfd ;
struct TYPE_3__ {int flags; } ;
typedef  TYPE_1__ asection ;

/* Variables and functions */
 int SEC_LOAD ; 
 TYPE_1__* bfd_get_section_by_name (int /*<<< orphan*/ *,char*) ; 
 struct spu_link_hash_table* spu_hash_table (struct bfd_link_info*) ; 

__attribute__((used)) static int
spu_elf_additional_program_headers (bfd *abfd, struct bfd_link_info *info)
{
  struct spu_link_hash_table *htab = spu_hash_table (info);
  int extra = htab->num_overlays;
  asection *sec;

  if (extra)
    ++extra;

  sec = bfd_get_section_by_name (abfd, ".toe");
  if (sec != NULL && (sec->flags & SEC_LOAD) != 0)
    ++extra;

  return extra;
}