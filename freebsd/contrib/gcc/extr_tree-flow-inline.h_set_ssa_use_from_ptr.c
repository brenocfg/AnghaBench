#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* use_operand_p ;
typedef  int /*<<< orphan*/  tree ;
struct TYPE_5__ {int /*<<< orphan*/ * use; } ;

/* Variables and functions */
 int /*<<< orphan*/  delink_imm_use (TYPE_1__*) ; 
 int /*<<< orphan*/  link_imm_use (TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void
set_ssa_use_from_ptr (use_operand_p use, tree val)
{
  delink_imm_use (use);
  *(use->use) = val;
  link_imm_use (use, val);
}