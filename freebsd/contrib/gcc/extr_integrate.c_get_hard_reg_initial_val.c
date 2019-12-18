#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct initial_value_struct {int num_entries; int max_entries; TYPE_1__* entries; } ;
typedef  scalar_t__ rtx ;
typedef  int /*<<< orphan*/  initial_value_struct ;
typedef  int /*<<< orphan*/  initial_value_pair ;
typedef  enum machine_mode { ____Placeholder_machine_mode } machine_mode ;
struct TYPE_5__ {struct initial_value_struct* hard_reg_initial_vals; } ;
struct TYPE_4__ {scalar_t__ pseudo; int /*<<< orphan*/  hard_reg; } ;

/* Variables and functions */
 TYPE_3__* cfun ; 
 scalar_t__ gen_reg_rtx (int) ; 
 int /*<<< orphan*/  gen_rtx_REG (int,unsigned int) ; 
 void* ggc_alloc (int) ; 
 TYPE_1__* ggc_realloc (TYPE_1__*,int) ; 
 scalar_t__ has_hard_reg_initial_val (int,unsigned int) ; 

rtx
get_hard_reg_initial_val (enum machine_mode mode, unsigned int regno)
{
  struct initial_value_struct *ivs;
  rtx rv;

  rv = has_hard_reg_initial_val (mode, regno);
  if (rv)
    return rv;

  ivs = cfun->hard_reg_initial_vals;
  if (ivs == 0)
    {
      ivs = ggc_alloc (sizeof (initial_value_struct));
      ivs->num_entries = 0;
      ivs->max_entries = 5;
      ivs->entries = ggc_alloc (5 * sizeof (initial_value_pair));
      cfun->hard_reg_initial_vals = ivs;
    }

  if (ivs->num_entries >= ivs->max_entries)
    {
      ivs->max_entries += 5;
      ivs->entries = ggc_realloc (ivs->entries,
				  ivs->max_entries
				  * sizeof (initial_value_pair));
    }

  ivs->entries[ivs->num_entries].hard_reg = gen_rtx_REG (mode, regno);
  ivs->entries[ivs->num_entries].pseudo = gen_reg_rtx (mode);

  return ivs->entries[ivs->num_entries++].pseudo;
}