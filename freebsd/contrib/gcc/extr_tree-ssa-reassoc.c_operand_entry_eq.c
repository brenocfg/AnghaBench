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
typedef  TYPE_1__* operand_entry_t ;
struct TYPE_2__ {scalar_t__ op; } ;

/* Variables and functions */

__attribute__((used)) static int
operand_entry_eq (const void *p1, const void *p2)
{
  const operand_entry_t vr1 = (operand_entry_t) p1;
  const operand_entry_t vr2 = (operand_entry_t) p2;
  return vr1->op == vr2->op;
}