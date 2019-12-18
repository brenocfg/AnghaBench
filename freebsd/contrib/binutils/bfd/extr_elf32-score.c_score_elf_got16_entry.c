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
struct score_got_entry {int gotidx; } ;
struct bfd_link_info {int dummy; } ;
typedef  int bfd_vma ;
typedef  int /*<<< orphan*/  bfd_boolean ;
typedef  int /*<<< orphan*/  bfd ;
typedef  int /*<<< orphan*/  asection ;
struct TYPE_2__ {int /*<<< orphan*/  dynobj; } ;

/* Variables and functions */
 int MINUS_ONE ; 
 int /*<<< orphan*/  R_SCORE_GOT15 ; 
 TYPE_1__* elf_hash_table (struct bfd_link_info*) ; 
 struct score_got_entry* score_elf_create_local_got_entry (int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct score_got_info*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct score_got_info* score_elf_got_info (int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int score_elf_high (int) ; 

__attribute__((used)) static bfd_vma
score_elf_got16_entry (bfd *abfd, bfd *ibfd, struct bfd_link_info *info,
		      bfd_vma value, bfd_boolean external)
{
  asection *sgot;
  struct score_got_info *g;
  struct score_got_entry *entry;

  if (!external)
    {
      /* Although the ABI says that it is "the high-order 16 bits" that we
	 want, it is really the %high value.  The complete value is
	 calculated with a `addiu' of a LO16 relocation, just as with a
	 HI16/LO16 pair.  */
      value = score_elf_high (value) << 16;
    }

  g = score_elf_got_info (elf_hash_table (info)->dynobj, &sgot);

  entry = score_elf_create_local_got_entry (abfd, ibfd, g, sgot, value, 0, NULL,
					    R_SCORE_GOT15);
  if (entry)
    return entry->gotidx;
  else
    return MINUS_ONE;
}