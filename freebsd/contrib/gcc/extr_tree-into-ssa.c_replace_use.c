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
typedef  int /*<<< orphan*/  use_operand_p ;
typedef  scalar_t__ tree ;

/* Variables and functions */
 int /*<<< orphan*/  SET_USE (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ get_reaching_def (scalar_t__) ; 

__attribute__((used)) static inline void
replace_use (use_operand_p use_p, tree use)
{
  tree rdef = get_reaching_def (use);
  if (rdef != use)
    SET_USE (use_p, rdef);
}