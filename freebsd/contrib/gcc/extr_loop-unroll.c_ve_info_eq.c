#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct var_to_expand {scalar_t__ insn; } ;

/* Variables and functions */

__attribute__((used)) static int
ve_info_eq (const void *ivts1, const void *ivts2)
{
  const struct var_to_expand *i1 = ivts1;
  const struct var_to_expand *i2 = ivts2;
  
  return i1->insn == i2->insn;
}