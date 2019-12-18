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
struct df_ref {struct df_ref* next_ref; } ;
struct df {int dummy; } ;
typedef  int /*<<< orphan*/  rtx ;
struct TYPE_2__ {struct df_ref* defs; } ;

/* Variables and functions */
 TYPE_1__* DF_INSN_UID_GET (struct df*,unsigned int) ; 
 int /*<<< orphan*/  DF_REF_REAL_REG (struct df_ref*) ; 
 scalar_t__ GET_CODE (int /*<<< orphan*/ ) ; 
 unsigned int INSN_UID (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REG_P (int /*<<< orphan*/ ) ; 
 scalar_t__ SUBREG ; 
 int /*<<< orphan*/  SUBREG_REG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gcc_assert (int /*<<< orphan*/ ) ; 
 scalar_t__ rtx_equal_p (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

struct df_ref *
df_find_def (struct df *df, rtx insn, rtx reg)
{
  unsigned int uid;
  struct df_ref *def;

  if (GET_CODE (reg) == SUBREG)
    reg = SUBREG_REG (reg);
  gcc_assert (REG_P (reg));

  uid = INSN_UID (insn);
  for (def = DF_INSN_UID_GET (df, uid)->defs; def; def = def->next_ref)
    if (rtx_equal_p (DF_REF_REAL_REG (def), reg))
      return def;

  return NULL;
}