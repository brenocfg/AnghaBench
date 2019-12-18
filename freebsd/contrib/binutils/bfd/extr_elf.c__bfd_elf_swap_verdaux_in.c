#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  bfd ;
struct TYPE_6__ {int /*<<< orphan*/  vda_next; int /*<<< orphan*/  vda_name; } ;
struct TYPE_5__ {void* vda_next; void* vda_name; } ;
typedef  TYPE_1__ Elf_Internal_Verdaux ;
typedef  TYPE_2__ Elf_External_Verdaux ;

/* Variables and functions */
 void* H_GET_32 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void
_bfd_elf_swap_verdaux_in (bfd *abfd,
			  const Elf_External_Verdaux *src,
			  Elf_Internal_Verdaux *dst)
{
  dst->vda_name = H_GET_32 (abfd, src->vda_name);
  dst->vda_next = H_GET_32 (abfd, src->vda_next);
}