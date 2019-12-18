#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__ value; } ;
struct aout_symbol {int /*<<< orphan*/  other; TYPE_4__ symbol; } ;
typedef  scalar_t__ bfd_vma ;
struct TYPE_6__ {scalar_t__ output_offset; TYPE_1__* output_section; } ;
typedef  TYPE_2__ asection ;
struct TYPE_5__ {scalar_t__ vma; } ;

/* Variables and functions */
 scalar_t__ IS_BALNAME (int /*<<< orphan*/ ) ; 
 scalar_t__ IS_CALLNAME (int /*<<< orphan*/ ) ; 
 TYPE_2__* bfd_get_section (TYPE_4__*) ; 

__attribute__((used)) static int
b_out_symbol_cmp (const void * a_ptr, const void * b_ptr)
{
  struct aout_symbol ** a = (struct aout_symbol **) a_ptr;
  struct aout_symbol ** b = (struct aout_symbol **) b_ptr;
  asection *sec;
  bfd_vma av, bv;

  /* Primary key is address.  */
  sec = bfd_get_section (&(*a)->symbol);
  av = sec->output_section->vma + sec->output_offset + (*a)->symbol.value;
  sec = bfd_get_section (&(*b)->symbol);
  bv = sec->output_section->vma + sec->output_offset + (*b)->symbol.value;

  if (av < bv)
    return -1;
  if (av > bv)
    return 1;

  /* Secondary key puts CALLNAME syms last and BALNAME syms first,
     so that they have the best chance of being contiguous.  */
  if (IS_BALNAME ((*a)->other) || IS_CALLNAME ((*b)->other))
    return -1;
  if (IS_CALLNAME ((*a)->other) || IS_BALNAME ((*b)->other))
    return 1;

  return 0;
}