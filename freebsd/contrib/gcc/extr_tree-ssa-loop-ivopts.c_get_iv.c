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
typedef  int /*<<< orphan*/  tree ;
struct ivopts_data {int /*<<< orphan*/  current_loop; } ;
struct iv {int dummy; } ;
typedef  int /*<<< orphan*/  basic_block ;
struct TYPE_2__ {struct iv* iv; } ;

/* Variables and functions */
 int /*<<< orphan*/  NULL_TREE ; 
 int /*<<< orphan*/  SSA_NAME_DEF_STMT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bb_for_stmt (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  flow_bb_inside_loop_p (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* name_info (struct ivopts_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_iv (struct ivopts_data*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct iv *
get_iv (struct ivopts_data *data, tree var)
{
  basic_block bb;
  
  if (!name_info (data, var)->iv)
    {
      bb = bb_for_stmt (SSA_NAME_DEF_STMT (var));

      if (!bb
	  || !flow_bb_inside_loop_p (data->current_loop, bb))
	set_iv (data, var, var, NULL_TREE);
    }

  return name_info (data, var)->iv;
}