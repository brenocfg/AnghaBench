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
struct asm_int_op {char const* hi; char const* si; char const* di; char const* ti; } ;
struct TYPE_3__ {char const* byte_op; struct asm_int_op unaligned_op; struct asm_int_op aligned_op; } ;
struct TYPE_4__ {TYPE_1__ asm_out; } ;

/* Variables and functions */
 TYPE_2__ targetm ; 

const char *
integer_asm_op (int size, int aligned_p)
{
  struct asm_int_op *ops;

  if (aligned_p)
    ops = &targetm.asm_out.aligned_op;
  else
    ops = &targetm.asm_out.unaligned_op;

  switch (size)
    {
    case 1:
      return targetm.asm_out.byte_op;
    case 2:
      return ops->hi;
    case 4:
      return ops->si;
    case 8:
      return ops->di;
    case 16:
      return ops->ti;
    default:
      return NULL;
    }
}