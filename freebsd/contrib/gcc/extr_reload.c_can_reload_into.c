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
struct recog_data {int dummy; } ;
typedef  int /*<<< orphan*/  rtx ;
typedef  enum machine_mode { ____Placeholder_machine_mode } machine_mode ;

/* Variables and functions */
 scalar_t__ MEM_P (int /*<<< orphan*/ ) ; 
 scalar_t__ REG_P (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VOIDmode ; 
 int constrain_operands (int) ; 
 int /*<<< orphan*/  extract_insn (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_rtx_REG (int,int) ; 
 int /*<<< orphan*/  gen_rtx_SET (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  make_insn_raw (int /*<<< orphan*/ ) ; 
 struct recog_data recog_data ; 
 scalar_t__ recog_memoized (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
can_reload_into (rtx in, int regno, enum machine_mode mode)
{
  rtx dst, test_insn;
  int r = 0;
  struct recog_data save_recog_data;

  /* For matching constraints, we often get notional input reloads where
     we want to use the original register as the reload register.  I.e.
     technically this is a non-optional input-output reload, but IN is
     already a valid register, and has been chosen as the reload register.
     Speed this up, since it trivially works.  */
  if (REG_P (in))
    return 1;

  /* To test MEMs properly, we'd have to take into account all the reloads
     that are already scheduled, which can become quite complicated.
     And since we've already handled address reloads for this MEM, it
     should always succeed anyway.  */
  if (MEM_P (in))
    return 1;

  /* If we can make a simple SET insn that does the job, everything should
     be fine.  */
  dst =  gen_rtx_REG (mode, regno);
  test_insn = make_insn_raw (gen_rtx_SET (VOIDmode, dst, in));
  save_recog_data = recog_data;
  if (recog_memoized (test_insn) >= 0)
    {
      extract_insn (test_insn);
      r = constrain_operands (1);
    }
  recog_data = save_recog_data;
  return r;
}