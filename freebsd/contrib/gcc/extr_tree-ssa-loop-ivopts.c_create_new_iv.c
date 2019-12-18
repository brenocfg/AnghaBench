#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tree ;
struct ivopts_data {int /*<<< orphan*/  current_loop; } ;
struct iv_cand {int pos; int /*<<< orphan*/  var_after; int /*<<< orphan*/  var_before; TYPE_1__* iv; } ;
typedef  int /*<<< orphan*/  block_stmt_iterator ;
struct TYPE_6__ {struct iv_cand* selected; } ;
struct TYPE_5__ {int preserve_biv; } ;
struct TYPE_4__ {int /*<<< orphan*/  step; int /*<<< orphan*/  base; } ;

/* Variables and functions */
#define  IP_END 130 
#define  IP_NORMAL 129 
#define  IP_ORIGINAL 128 
 int /*<<< orphan*/  add_referenced_var (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bsi_last (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  create_iv (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_3__* find_interesting_uses_op (struct ivopts_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gimple_add_tmp_var (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ip_end_pos (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ip_normal_pos (int /*<<< orphan*/ ) ; 
 TYPE_2__* name_info (struct ivopts_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unshare_expr (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
create_new_iv (struct ivopts_data *data, struct iv_cand *cand)
{
  block_stmt_iterator incr_pos;
  tree base;
  bool after = false;

  if (!cand->iv)
    return;

  switch (cand->pos)
    {
    case IP_NORMAL:
      incr_pos = bsi_last (ip_normal_pos (data->current_loop));
      break;

    case IP_END:
      incr_pos = bsi_last (ip_end_pos (data->current_loop));
      after = true;
      break;

    case IP_ORIGINAL:
      /* Mark that the iv is preserved.  */
      name_info (data, cand->var_before)->preserve_biv = true;
      name_info (data, cand->var_after)->preserve_biv = true;

      /* Rewrite the increment so that it uses var_before directly.  */
      find_interesting_uses_op (data, cand->var_after)->selected = cand;
      
      return;
    }
 
  gimple_add_tmp_var (cand->var_before);
  add_referenced_var (cand->var_before);

  base = unshare_expr (cand->iv->base);

  create_iv (base, unshare_expr (cand->iv->step),
	     cand->var_before, data->current_loop,
	     &incr_pos, after, &cand->var_before, &cand->var_after);
}