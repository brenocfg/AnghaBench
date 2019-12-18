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
struct see_entry_extra_info {int relevancy; int local_relevancy; } ;
typedef  int /*<<< orphan*/ * rtx ;
typedef  enum entry_type { ____Placeholder_entry_type } entry_type ;
struct TYPE_2__ {int /*<<< orphan*/ * pred; int /*<<< orphan*/ * reg; struct see_entry_extra_info* extra_info; } ;

/* Variables and functions */
 int /*<<< orphan*/ * DF_REF_INSN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * DF_REF_REAL_REG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DF_USES_GET (int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  INSN_P (int /*<<< orphan*/ *) ; 
 int INSN_UID (int /*<<< orphan*/ *) ; 
 int NOT_RELEVANT ; 
 int /*<<< orphan*/  NULL_RTX ; 
 int REGNO (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  REG_LIBCALL ; 
 int /*<<< orphan*/  REG_RETVAL ; 
 int RELEVANT_USE ; 
 int /*<<< orphan*/  df ; 
 scalar_t__ dump_file ; 
 scalar_t__ find_reg_note (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (scalar_t__,char*,...) ; 
 TYPE_1__* use_entry ; 
 unsigned int uses_num ; 
 struct see_entry_extra_info* xmalloc (int) ; 

__attribute__((used)) static void
see_update_uses_relevancy (void)
{
  rtx insn = NULL;
  rtx reg = NULL;
  struct see_entry_extra_info *curr_entry_extra_info;
  enum entry_type et;
  unsigned int i;

  if (!df || !use_entry)
    return;

  for (i = 0; i < uses_num; i++)
    {

      insn = DF_REF_INSN (DF_USES_GET (df, i));
      reg = DF_REF_REAL_REG (DF_USES_GET (df, i));

      et = RELEVANT_USE;

      if (insn) 
	{
	  if (!INSN_P (insn))
	    et = NOT_RELEVANT;
	  if (insn && find_reg_note (insn, REG_LIBCALL, NULL_RTX))
	    et = NOT_RELEVANT;
	  if (find_reg_note (insn, REG_RETVAL, NULL_RTX))
	    et = NOT_RELEVANT;
	}
      else
	et = NOT_RELEVANT;

      if (dump_file)
	{
	  fprintf (dump_file, "u%i insn %i reg %i ", 
          i, (insn ? INSN_UID (insn) : -1), REGNO (reg));
	  if (et == NOT_RELEVANT)
	    fprintf (dump_file, "NOT RELEVANT \n");
	  else
	    fprintf (dump_file, "RELEVANT USE \n");
	}

      curr_entry_extra_info = xmalloc (sizeof (struct see_entry_extra_info));
      curr_entry_extra_info->relevancy = et;
      curr_entry_extra_info->local_relevancy = et;
      use_entry[i].extra_info = curr_entry_extra_info;
      use_entry[i].reg = NULL;
      use_entry[i].pred = NULL;
    }
}