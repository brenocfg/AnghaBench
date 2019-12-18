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
struct score_got_info {int dummy; } ;
struct score_got_entry {int /*<<< orphan*/  gotidx; } ;
struct score_elf_link_hash_entry {int dummy; } ;
struct bfd_link_info {int dummy; } ;
typedef  int /*<<< orphan*/  bfd_vma ;
typedef  int /*<<< orphan*/  bfd ;
typedef  int /*<<< orphan*/  asection ;
struct TYPE_2__ {int /*<<< orphan*/  dynobj; } ;

/* Variables and functions */
 int /*<<< orphan*/  MINUS_ONE ; 
 TYPE_1__* elf_hash_table (struct bfd_link_info*) ; 
 struct score_got_entry* score_elf_create_local_got_entry (int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct score_got_info*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned long,struct score_elf_link_hash_entry*,int) ; 
 struct score_got_info* score_elf_got_info (int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 

__attribute__((used)) static bfd_vma
score_elf_local_got_index (bfd *abfd, bfd *ibfd, struct bfd_link_info *info,
			  bfd_vma value, unsigned long r_symndx,
			  struct score_elf_link_hash_entry *h, int r_type)
{
  asection *sgot;
  struct score_got_info *g;
  struct score_got_entry *entry;

  g = score_elf_got_info (elf_hash_table (info)->dynobj, &sgot);

  entry = score_elf_create_local_got_entry (abfd, ibfd, g, sgot, value,
		 			    r_symndx, h, r_type);
  if (!entry)
    return MINUS_ONE;

  else
    return entry->gotidx;
}