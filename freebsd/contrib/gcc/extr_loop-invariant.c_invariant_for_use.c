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
struct invariant {int dummy; } ;
struct df_ref {int flags; int /*<<< orphan*/  insn; } ;
struct df_link {struct df_ref* ref; scalar_t__ next; } ;
typedef  int /*<<< orphan*/  basic_block ;

/* Variables and functions */
 int /*<<< orphan*/  BLOCK_FOR_INSN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CDI_DOMINATORS ; 
 int /*<<< orphan*/  DF_REF_BB (struct df_ref*) ; 
 struct df_link* DF_REF_CHAIN (struct df_ref*) ; 
 struct invariant* DF_REF_DATA (struct df_ref*) ; 
 int DF_REF_READ_WRITE ; 
 int /*<<< orphan*/  dominated_by_p (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct invariant *
invariant_for_use (struct df_ref *use)
{
  struct df_link *defs;
  struct df_ref *def;
  basic_block bb = BLOCK_FOR_INSN (use->insn), def_bb;

  if (use->flags & DF_REF_READ_WRITE)
    return NULL;

  defs = DF_REF_CHAIN (use);
  if (!defs || defs->next)
    return NULL;
  def = defs->ref;
  if (!DF_REF_DATA (def))
    return NULL;

  def_bb = DF_REF_BB (def);
  if (!dominated_by_p (CDI_DOMINATORS, bb, def_bb))
    return NULL;
  return DF_REF_DATA (def);
}