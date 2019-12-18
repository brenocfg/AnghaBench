#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  bfd ;
struct TYPE_7__ {int /*<<< orphan*/  d_val; } ;
struct TYPE_9__ {TYPE_2__ d_un; int /*<<< orphan*/  d_tag; } ;
struct TYPE_6__ {int /*<<< orphan*/  d_val; } ;
struct TYPE_8__ {TYPE_1__ d_un; int /*<<< orphan*/  d_tag; } ;
typedef  TYPE_3__ Elf_Internal_Dyn ;
typedef  TYPE_4__ Elf_External_Dyn ;

/* Variables and functions */
 int /*<<< orphan*/  H_PUT_WORD (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
elf_swap_dyn_out (bfd *abfd,
		  const Elf_Internal_Dyn *src,
		  void *p)
{
  Elf_External_Dyn *dst = p;

  H_PUT_WORD (abfd, src->d_tag, dst->d_tag);
  H_PUT_WORD (abfd, src->d_un.d_val, dst->d_un.d_val);
}