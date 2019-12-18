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
typedef  TYPE_1__* stmt_operands_p ;
struct TYPE_3__ {int /*<<< orphan*/ * vuse_ops; int /*<<< orphan*/ * mustdef_ops; int /*<<< orphan*/ * maydef_ops; int /*<<< orphan*/ * use_ops; int /*<<< orphan*/ * def_ops; } ;

/* Variables and functions */

void 
free_ssa_operands (stmt_operands_p ops)
{
  ops->def_ops = NULL;
  ops->use_ops = NULL;
  ops->maydef_ops = NULL;
  ops->mustdef_ops = NULL;
  ops->vuse_ops = NULL;
}