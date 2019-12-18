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
typedef  scalar_t__ rtx ;

/* Variables and functions */
 int /*<<< orphan*/  VOIDmode ; 
 int /*<<< orphan*/  copy_rtx (scalar_t__) ; 
 int /*<<< orphan*/  emit_insn (scalar_t__) ; 
 scalar_t__ gen_rtx_COND_EXEC (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void
emit_constant_insn (rtx cond, rtx pattern)
{
  if (cond)
    pattern = gen_rtx_COND_EXEC (VOIDmode, copy_rtx (cond), pattern);
  emit_insn (pattern);
}