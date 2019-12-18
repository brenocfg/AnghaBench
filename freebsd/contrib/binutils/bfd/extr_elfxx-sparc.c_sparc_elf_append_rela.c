#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct elf_backend_data {TYPE_1__* s; } ;
typedef  int /*<<< orphan*/  bfd_byte ;
typedef  int /*<<< orphan*/  bfd ;
struct TYPE_5__ {int /*<<< orphan*/  reloc_count; int /*<<< orphan*/ * contents; } ;
typedef  TYPE_2__ asection ;
struct TYPE_4__ {int sizeof_rela; int /*<<< orphan*/  (* swap_reloca_out ) (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ;} ;
typedef  int /*<<< orphan*/  Elf_Internal_Rela ;

/* Variables and functions */
 struct elf_backend_data* get_elf_backend_data (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
sparc_elf_append_rela (bfd *abfd, asection *s, Elf_Internal_Rela *rel)
{
  const struct elf_backend_data *bed;
  bfd_byte *loc;

  bed = get_elf_backend_data (abfd);
  loc = s->contents + (s->reloc_count++ * bed->s->sizeof_rela);
  bed->s->swap_reloca_out (abfd, rel, loc);
}