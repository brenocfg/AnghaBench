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
struct initial_value_struct {int num_entries; TYPE_1__* entries; } ;
struct function {struct initial_value_struct* hard_reg_initial_vals; } ;
typedef  int /*<<< orphan*/  rtx ;
struct TYPE_2__ {int /*<<< orphan*/  hard_reg; int /*<<< orphan*/  pseudo; } ;

/* Variables and functions */
 int /*<<< orphan*/  NULL_RTX ; 
 scalar_t__ rtx_equal_p (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

rtx
get_hard_reg_initial_reg (struct function *fun, rtx reg)
{
  struct initial_value_struct *ivs = fun->hard_reg_initial_vals;
  int i;

  if (ivs == 0)
    return NULL_RTX;

  for (i = 0; i < ivs->num_entries; i++)
    if (rtx_equal_p (ivs->entries[i].pseudo, reg))
      return ivs->entries[i].hard_reg;

  return NULL_RTX;
}