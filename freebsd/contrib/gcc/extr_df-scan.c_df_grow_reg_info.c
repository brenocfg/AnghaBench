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
struct df_scan_problem_data {int /*<<< orphan*/  reg_pool; } ;
struct df_reg_info {int dummy; } ;
struct df_ref_info {unsigned int regs_size; unsigned int regs_inited; struct df_reg_info** regs; } ;
struct dataflow {scalar_t__ problem_data; } ;

/* Variables and functions */
 unsigned int max_reg_num () ; 
 int /*<<< orphan*/  memset (struct df_reg_info*,int /*<<< orphan*/ ,int) ; 
 struct df_reg_info* pool_alloc (int /*<<< orphan*/ ) ; 
 struct df_reg_info** xrealloc (struct df_reg_info**,unsigned int) ; 

__attribute__((used)) static void 
df_grow_reg_info (struct dataflow *dflow, struct df_ref_info *ref_info)
{
  unsigned int max_reg = max_reg_num ();
  unsigned int new_size = max_reg;
  struct df_scan_problem_data *problem_data
    = (struct df_scan_problem_data *) dflow->problem_data;
  unsigned int i;

  if (ref_info->regs_size < new_size)
    {
      new_size += new_size / 4;
      ref_info->regs = xrealloc (ref_info->regs, 
				 new_size *sizeof (struct df_reg_info*));
      ref_info->regs_size = new_size;
    }

  for (i = ref_info->regs_inited; i < max_reg; i++)
    {
      struct df_reg_info *reg_info = pool_alloc (problem_data->reg_pool);
      memset (reg_info, 0, sizeof (struct df_reg_info));
      ref_info->regs[i] = reg_info;
    }
  
  ref_info->regs_inited = max_reg;
}