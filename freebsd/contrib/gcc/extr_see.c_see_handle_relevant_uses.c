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
struct web_entry {int /*<<< orphan*/ * reg; } ;
typedef  int /*<<< orphan*/ * rtx ;
typedef  enum rtx_code { ____Placeholder_rtx_code } rtx_code ;
struct TYPE_2__ {scalar_t__ relevancy; int /*<<< orphan*/  source_mode; } ;

/* Variables and functions */
 int /*<<< orphan*/ * DF_REF_INSN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * DF_REF_REAL_REG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DF_USES_GET (int /*<<< orphan*/ ,unsigned int) ; 
 TYPE_1__* ENTRY_EI (struct web_entry*) ; 
 int /*<<< orphan*/  INSN_P (int /*<<< orphan*/ *) ; 
 int SIGN_EXTEND ; 
 scalar_t__ SIGN_EXTENDED_DEF ; 
 int /*<<< orphan*/  USE_EXTENSION ; 
 int ZERO_EXTEND ; 
 scalar_t__ ZERO_EXTENDED_DEF ; 
 int /*<<< orphan*/  df ; 
 int /*<<< orphan*/  gcc_assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtx_equal_p (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * see_gen_normalized_extension (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  see_store_reference_and_extension (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct web_entry* unionfind_root (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * use_entry ; 
 unsigned int uses_num ; 

__attribute__((used)) static int
see_handle_relevant_uses (void)
{
  rtx insn = NULL;
  rtx reg = NULL;
  struct web_entry *root_entry = NULL;
  rtx se_insn = NULL;
  unsigned int i;
  int num_relevant_uses = 0;
  enum rtx_code extension_code;

  for (i = 0; i < uses_num; i++)
    {
      insn = DF_REF_INSN (DF_USES_GET (df, i));
      reg = DF_REF_REAL_REG (DF_USES_GET (df, i));

      if (!insn)
	continue;

      if (!INSN_P (insn))
	continue;

      root_entry = unionfind_root (&use_entry[i]);

      if (ENTRY_EI (root_entry)->relevancy != SIGN_EXTENDED_DEF
	  && ENTRY_EI (root_entry)->relevancy != ZERO_EXTENDED_DEF)
	/* The current web is not relevant.  Continue to the next use.  */
	continue;

      if (root_entry->reg)
	/* It isn't possible to have two different register for the same
	   web.  */
	gcc_assert (rtx_equal_p (root_entry->reg, reg));
      else
	root_entry->reg = reg;

      /* Generate the use extension.  */
      if (ENTRY_EI (root_entry)->relevancy == SIGN_EXTENDED_DEF)
	extension_code = SIGN_EXTEND;
      else
	extension_code = ZERO_EXTEND;

      se_insn =
	see_gen_normalized_extension (reg, extension_code,
				      ENTRY_EI (root_entry)->source_mode);
      if (!se_insn)
	/* This is very bad, abort the transformation.  */
	return -1;

      num_relevant_uses++;

      if (!see_store_reference_and_extension (insn, se_insn,
      					      USE_EXTENSION))
	/* Something bad happened.  Abort the optimization.  */
	return -1;
    }

  return num_relevant_uses;
}