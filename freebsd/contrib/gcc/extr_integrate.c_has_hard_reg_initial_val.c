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
struct initial_value_struct {int num_entries; TYPE_1__* entries; } ;
typedef  int /*<<< orphan*/  rtx ;
typedef  enum machine_mode { ____Placeholder_machine_mode } machine_mode ;
struct TYPE_4__ {struct initial_value_struct* hard_reg_initial_vals; } ;
struct TYPE_3__ {int /*<<< orphan*/  pseudo; int /*<<< orphan*/  hard_reg; } ;

/* Variables and functions */
 int GET_MODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NULL_RTX ; 
 unsigned int REGNO (int /*<<< orphan*/ ) ; 
 TYPE_2__* cfun ; 

rtx
has_hard_reg_initial_val (enum machine_mode mode, unsigned int regno)
{
  struct initial_value_struct *ivs;
  int i;

  ivs = cfun->hard_reg_initial_vals;
  if (ivs != 0)
    for (i = 0; i < ivs->num_entries; i++)
      if (GET_MODE (ivs->entries[i].hard_reg) == mode
	  && REGNO (ivs->entries[i].hard_reg) == regno)
	return ivs->entries[i].pseudo;

  return NULL_RTX;
}