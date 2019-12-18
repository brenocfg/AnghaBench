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

/* Variables and functions */
 int /*<<< orphan*/  CCmode ; 
 int /*<<< orphan*/  GET_MODE (int /*<<< orphan*/ ) ; 
 int GET_MODE_SIZE (int /*<<< orphan*/ ) ; 
 int REGNO (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SImode ; 
 int /*<<< orphan*/  TARGET_USE_MOV0 ; 
 int /*<<< orphan*/  VOIDmode ; 
 int /*<<< orphan*/  const0_rtx ; 
 int /*<<< orphan*/  emit_insn (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gcc_assert (scalar_t__) ; 
 int /*<<< orphan*/  gen_rtvec (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_rtx_CLOBBER (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_rtx_PARALLEL (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_rtx_REG (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  gen_rtx_SET (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ optimize_size ; 
 scalar_t__ reload_completed ; 

void
ix86_expand_clear (rtx dest)
{
  rtx tmp;

  /* We play register width games, which are only valid after reload.  */
  gcc_assert (reload_completed);

  /* Avoid HImode and its attendant prefix byte.  */
  if (GET_MODE_SIZE (GET_MODE (dest)) < 4)
    dest = gen_rtx_REG (SImode, REGNO (dest));

  tmp = gen_rtx_SET (VOIDmode, dest, const0_rtx);

  /* This predicate should match that for movsi_xor and movdi_xor_rex64.  */
  if (reload_completed && (!TARGET_USE_MOV0 || optimize_size))
    {
      rtx clob = gen_rtx_CLOBBER (VOIDmode, gen_rtx_REG (CCmode, 17));
      tmp = gen_rtx_PARALLEL (VOIDmode, gen_rtvec (2, tmp, clob));
    }

  emit_insn (tmp);
}