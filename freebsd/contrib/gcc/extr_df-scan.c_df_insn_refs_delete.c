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
struct df_scan_problem_data {int /*<<< orphan*/  insn_pool; int /*<<< orphan*/  mw_reg_pool; int /*<<< orphan*/  mw_link_pool; } ;
struct df_ref {int dummy; } ;
struct df_mw_hardreg {struct df_ref* uses; struct df_ref* defs; struct df_mw_hardreg* next; struct df_mw_hardreg* regs; struct df_mw_hardreg* mw_hardregs; } ;
struct df_link {struct df_ref* uses; struct df_ref* defs; struct df_link* next; struct df_link* regs; struct df_link* mw_hardregs; } ;
struct df_insn_info {struct df_ref* uses; struct df_ref* defs; struct df_insn_info* next; struct df_insn_info* regs; struct df_insn_info* mw_hardregs; } ;
struct df {unsigned int insns_size; } ;
struct dataflow {scalar_t__ problem_data; struct df* df; } ;
typedef  int /*<<< orphan*/  rtx ;

/* Variables and functions */
 int /*<<< orphan*/  DF_INSN_SET (struct df*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct df_mw_hardreg* DF_INSN_UID_GET (struct df*,unsigned int) ; 
 unsigned int INSN_UID (int /*<<< orphan*/ ) ; 
 struct df_ref* df_reg_chain_unlink (struct dataflow*,struct df_ref*) ; 
 int /*<<< orphan*/  pool_free (int /*<<< orphan*/ ,struct df_mw_hardreg*) ; 

void 
df_insn_refs_delete (struct dataflow *dflow, rtx insn)
{
  struct df *df = dflow->df;
  unsigned int uid = INSN_UID (insn);
  struct df_insn_info *insn_info = NULL;
  struct df_ref *ref;
  struct df_scan_problem_data *problem_data
    = (struct df_scan_problem_data *) dflow->problem_data;

  if (uid < df->insns_size)
    insn_info = DF_INSN_UID_GET (df, uid);

  if (insn_info)
    {
      struct df_mw_hardreg *hardregs = insn_info->mw_hardregs;
      
      while (hardregs)
	{
	  struct df_mw_hardreg *next_hr = hardregs->next;
	  struct df_link *link = hardregs->regs;
	  while (link)
	    {
	      struct df_link *next_l = link->next;
	      pool_free (problem_data->mw_link_pool, link);
	      link = next_l;
	    }
	  
	  pool_free (problem_data->mw_reg_pool, hardregs);
	  hardregs = next_hr;
	}

      ref = insn_info->defs;
      while (ref) 
	ref = df_reg_chain_unlink (dflow, ref);
      
      ref = insn_info->uses;
      while (ref) 
	ref = df_reg_chain_unlink (dflow, ref);

      pool_free (problem_data->insn_pool, insn_info);
      DF_INSN_SET (df, insn, NULL);
    }
}