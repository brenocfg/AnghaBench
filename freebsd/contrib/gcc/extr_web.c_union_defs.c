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
struct web_entry {int dummy; } ;
struct df_ref {int flags; struct df_ref* next_ref; } ;
struct df_link {struct df_link* next; struct df_ref* ref; } ;
struct df {int dummy; } ;
typedef  int /*<<< orphan*/ * rtx ;

/* Variables and functions */
 struct df_ref* DF_INSN_DEFS (struct df*,int /*<<< orphan*/ *) ; 
 struct df_ref* DF_INSN_USES (struct df*,int /*<<< orphan*/ *) ; 
 struct df_link* DF_REF_CHAIN (struct df_ref*) ; 
 int DF_REF_ID (struct df_ref*) ; 
 int /*<<< orphan*/ * DF_REF_INSN (struct df_ref*) ; 
 int DF_REF_READ_WRITE ; 
 scalar_t__ DF_REF_REAL_REG (struct df_ref*) ; 
 scalar_t__ DF_REF_REG (struct df_ref*) ; 
 scalar_t__ SET_DEST (int /*<<< orphan*/ *) ; 
 scalar_t__ SET_SRC (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * single_set (int /*<<< orphan*/ *) ; 
 int stub1 (struct web_entry*,struct web_entry*) ; 
 int stub2 (struct web_entry*,struct web_entry*) ; 
 int stub3 (struct web_entry*,struct web_entry*) ; 
 int stub4 (struct web_entry*,struct web_entry*) ; 

void
union_defs (struct df *df, struct df_ref *use, struct web_entry *def_entry,
 	    struct web_entry *use_entry,
 	    bool (*fun) (struct web_entry *, struct web_entry *))
{
  rtx insn = DF_REF_INSN (use);
  struct df_link *link = DF_REF_CHAIN (use);
  struct df_ref *use_link;
  struct df_ref *def_link;
  rtx set;

  if (insn)
    {
      use_link = DF_INSN_USES (df, insn);
      def_link = DF_INSN_DEFS (df, insn);
      set = single_set (insn);
    }
  else
    {
      use_link = NULL;
      def_link = NULL;
      set = NULL;
    }

  /* Some instructions may use match_dup for their operands.  In case the
     operands are dead, we will assign them different pseudos, creating
     invalid instructions, so union all uses of the same operand for each
     insn.  */

  while (use_link)
    {
      if (use != use_link
	  && DF_REF_REAL_REG (use) == DF_REF_REAL_REG (use_link))
 	(*fun) (use_entry + DF_REF_ID (use),
 		use_entry + DF_REF_ID (use_link));
      use_link = use_link->next_ref;
    }

  /* Recognize trivial noop moves and attempt to keep them as noop.
     While most of noop moves should be removed, we still keep some
     of them at libcall boundaries and such.  */

  if (set
      && SET_SRC (set) == DF_REF_REG (use)
      && SET_SRC (set) == SET_DEST (set))
    {
      while (def_link)
	{
	  if (DF_REF_REAL_REG (use) == DF_REF_REAL_REG (def_link))
 	    (*fun) (use_entry + DF_REF_ID (use),
 		    def_entry + DF_REF_ID (def_link));
	  def_link = def_link->next_ref;
	}
    }
  while (link)
    {
      (*fun) (use_entry + DF_REF_ID (use),
	      def_entry + DF_REF_ID (link->ref));
      link = link->next;
    }

  /* A READ_WRITE use requires the corresponding def to be in the same
     register.  Find it and union.  */
  if (use->flags & DF_REF_READ_WRITE)
    {
      struct df_ref *link;

      if (DF_REF_INSN (use))
	link = DF_INSN_DEFS (df, DF_REF_INSN (use));
      else
	link = NULL;

      while (link)
	{
	  if (DF_REF_REAL_REG (link) == DF_REF_REAL_REG (use))
 	    (*fun) (use_entry + DF_REF_ID (use),
 		    def_entry + DF_REF_ID (link));
	  link = link->next_ref;
	}
    }
}