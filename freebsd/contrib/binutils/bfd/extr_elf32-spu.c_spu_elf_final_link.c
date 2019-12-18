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
struct spu_link_hash_table {int /*<<< orphan*/  emit_stack_syms; scalar_t__ stack_analysis; } ;
struct bfd_link_info {TYPE_1__* callbacks; } ;
typedef  int /*<<< orphan*/  bfd_boolean ;
typedef  int /*<<< orphan*/  bfd ;
struct TYPE_2__ {int /*<<< orphan*/  (* einfo ) (char*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  bfd_elf_final_link (int /*<<< orphan*/ *,struct bfd_link_info*) ; 
 int /*<<< orphan*/  spu_elf_stack_analysis (int /*<<< orphan*/ *,struct bfd_link_info*,int /*<<< orphan*/ ) ; 
 struct spu_link_hash_table* spu_hash_table (struct bfd_link_info*) ; 
 int /*<<< orphan*/  stub1 (char*) ; 

__attribute__((used)) static bfd_boolean
spu_elf_final_link (bfd *output_bfd, struct bfd_link_info *info)
{
  struct spu_link_hash_table *htab = spu_hash_table (info);

  if (htab->stack_analysis
      && !spu_elf_stack_analysis (output_bfd, info, htab->emit_stack_syms))
    info->callbacks->einfo ("%X%P: stack analysis error: %E\n");

  return bfd_elf_final_link (output_bfd, info);
}