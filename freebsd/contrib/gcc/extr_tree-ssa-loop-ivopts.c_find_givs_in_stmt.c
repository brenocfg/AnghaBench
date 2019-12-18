#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tree ;
struct ivopts_data {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  step; int /*<<< orphan*/  base; } ;
typedef  TYPE_1__ affine_iv ;

/* Variables and functions */
 int /*<<< orphan*/  TREE_OPERAND (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  find_givs_in_stmt_scev (struct ivopts_data*,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  set_iv (struct ivopts_data*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
find_givs_in_stmt (struct ivopts_data *data, tree stmt)
{
  affine_iv iv;

  if (!find_givs_in_stmt_scev (data, stmt, &iv))
    return;

  set_iv (data, TREE_OPERAND (stmt, 0), iv.base, iv.step);
}