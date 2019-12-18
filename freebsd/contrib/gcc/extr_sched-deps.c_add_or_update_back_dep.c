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
typedef  int /*<<< orphan*/  rtx ;
typedef  enum reg_note { ____Placeholder_reg_note } reg_note ;
typedef  enum DEPS_ADJUST_RESULT { ____Placeholder_DEPS_ADJUST_RESULT } DEPS_ADJUST_RESULT ;
typedef  int /*<<< orphan*/  ds_t ;

/* Variables and functions */
 int add_or_update_back_dep_1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

enum DEPS_ADJUST_RESULT
add_or_update_back_dep (rtx insn, rtx elem, enum reg_note dep_type, ds_t ds)
{
  return add_or_update_back_dep_1 (insn, elem, dep_type, ds, 0, 0, 0);
}