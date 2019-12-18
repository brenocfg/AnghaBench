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
struct df_ref {struct df_ref* next_ref; int /*<<< orphan*/ * chain; } ;
struct df_insn_info {struct df_ref* uses; struct df_ref* defs; } ;
struct df {unsigned int insns_size; } ;
struct dataflow {int flags; struct df* df; } ;
typedef  int /*<<< orphan*/  rtx ;

/* Variables and functions */
 int DF_DU_CHAIN ; 
 struct df_insn_info* DF_INSN_UID_GET (struct df*,unsigned int) ; 
 int DF_UD_CHAIN ; 
 unsigned int INSN_UID (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void 
df_chain_insn_reset (struct dataflow *dflow, rtx insn)
{
  struct df *df = dflow->df;
  unsigned int uid = INSN_UID (insn);
  struct df_insn_info *insn_info = NULL;
  struct df_ref *ref;

  if (uid < df->insns_size)
    insn_info = DF_INSN_UID_GET (df, uid);

  if (insn_info)
    {
      if (dflow->flags & DF_DU_CHAIN)
	{
	  ref = insn_info->defs;
	  while (ref)
	    {
	      ref->chain = NULL;
	      ref = ref->next_ref;
	    }
	}

      if (dflow->flags & DF_UD_CHAIN)
	{
	  ref = insn_info->uses;
	  while (ref) 
	    {
	      ref->chain = NULL;
	      ref = ref->next_ref;
	    }
	}
    }
}