#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int sym_mask; } ;
struct elf_link_sort_rela {scalar_t__ type; TYPE_2__* rela; TYPE_1__ u; } ;
struct TYPE_4__ {int r_info; scalar_t__ r_offset; } ;

/* Variables and functions */
 scalar_t__ reloc_class_relative ; 

__attribute__((used)) static int
elf_link_sort_cmp1 (const void *A, const void *B)
{
  const struct elf_link_sort_rela *a = A;
  const struct elf_link_sort_rela *b = B;
  int relativea, relativeb;

  relativea = a->type == reloc_class_relative;
  relativeb = b->type == reloc_class_relative;

  if (relativea < relativeb)
    return 1;
  if (relativea > relativeb)
    return -1;
  if ((a->rela->r_info & a->u.sym_mask) < (b->rela->r_info & b->u.sym_mask))
    return -1;
  if ((a->rela->r_info & a->u.sym_mask) > (b->rela->r_info & b->u.sym_mask))
    return 1;
  if (a->rela->r_offset < b->rela->r_offset)
    return -1;
  if (a->rela->r_offset > b->rela->r_offset)
    return 1;
  return 0;
}