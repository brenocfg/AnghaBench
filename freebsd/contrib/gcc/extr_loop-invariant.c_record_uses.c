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
struct invariant {int /*<<< orphan*/  def; } ;
struct df_ref {struct df_ref* next_ref; } ;
typedef  int /*<<< orphan*/  rtx ;
struct TYPE_2__ {struct df_ref* uses; } ;

/* Variables and functions */
 TYPE_1__* DF_INSN_GET (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DF_REF_INSN (struct df_ref*) ; 
 int /*<<< orphan*/  DF_REF_LOC (struct df_ref*) ; 
 int /*<<< orphan*/  df ; 
 struct invariant* invariant_for_use (struct df_ref*) ; 
 int /*<<< orphan*/  record_use (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
record_uses (rtx insn)
{
  struct df_ref *use;
  struct invariant *inv;

  for (use = DF_INSN_GET (df, insn)->uses; use; use = use->next_ref)
    {
      inv = invariant_for_use (use);
      if (inv)
	record_use (inv->def, DF_REF_LOC (use), DF_REF_INSN (use));
    }
}