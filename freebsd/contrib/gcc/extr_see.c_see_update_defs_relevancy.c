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
struct see_entry_extra_info {int relevancy; int local_relevancy; int source_mode; int local_source_mode; int source_mode_signed; int source_mode_unsigned; } ;
typedef  int /*<<< orphan*/ * rtx ;
typedef  enum machine_mode { ____Placeholder_machine_mode } machine_mode ;
typedef  enum entry_type { ____Placeholder_entry_type } entry_type ;
struct TYPE_2__ {int /*<<< orphan*/ * pred; int /*<<< orphan*/ * reg; struct see_entry_extra_info* extra_info; } ;

/* Variables and functions */
 int /*<<< orphan*/  DF_DEFS_GET (int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/ * DF_REF_INSN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * DF_REF_REAL_REG (int /*<<< orphan*/ ) ; 
#define  EXTENDED_DEF 130 
 char* GET_MODE_NAME (int) ; 
 int INSN_UID (int /*<<< orphan*/ *) ; 
 int MAX_MACHINE_MODE ; 
 int NOT_RELEVANT ; 
 int REGNO (int /*<<< orphan*/ *) ; 
#define  SIGN_EXTENDED_DEF 129 
#define  ZERO_EXTENDED_DEF 128 
 TYPE_1__* def_entry ; 
 unsigned int defs_num ; 
 int /*<<< orphan*/  df ; 
 scalar_t__ dump_file ; 
 int /*<<< orphan*/  fprintf (scalar_t__,char*,...) ; 
 int /*<<< orphan*/  gcc_unreachable () ; 
 int see_analyze_one_def (int /*<<< orphan*/ *,int*,int*) ; 
 struct see_entry_extra_info* xmalloc (int) ; 

__attribute__((used)) static void
see_update_defs_relevancy (void)
{
  struct see_entry_extra_info *curr_entry_extra_info;
  unsigned int i;
  rtx insn = NULL;
  rtx reg = NULL;
  enum entry_type et;
  enum machine_mode source_mode;
  enum machine_mode source_mode_unsigned;

  if (!df || !def_entry)
    return;

  for (i = 0; i < defs_num; i++)
    {
      insn = DF_REF_INSN (DF_DEFS_GET (df, i));
      reg = DF_REF_REAL_REG (DF_DEFS_GET (df, i));

      et = see_analyze_one_def (insn, &source_mode, &source_mode_unsigned);

      curr_entry_extra_info = xmalloc (sizeof (struct see_entry_extra_info));
      curr_entry_extra_info->relevancy = et;
      curr_entry_extra_info->local_relevancy = et;
      if (et != EXTENDED_DEF)
	{
	  curr_entry_extra_info->source_mode = source_mode;
	  curr_entry_extra_info->local_source_mode = source_mode;
	}
      else
	{
	  curr_entry_extra_info->source_mode_signed = source_mode;
	  curr_entry_extra_info->source_mode_unsigned = source_mode_unsigned;
	}
      def_entry[i].extra_info = curr_entry_extra_info;
      def_entry[i].reg = NULL;
      def_entry[i].pred = NULL;

      if (dump_file)
	{
	  if (et == NOT_RELEVANT)
	    {
	      fprintf (dump_file, "d%i insn %i reg %i ",
              i, (insn ? INSN_UID (insn) : -1), REGNO (reg));
	      fprintf (dump_file, "NOT RELEVANT \n");
	    }
	  else
	    {
	      fprintf (dump_file, "d%i insn %i reg %i ",
		       i ,INSN_UID (insn), REGNO (reg));
	      fprintf (dump_file, "RELEVANT - ");
	      switch (et)
		{
		case SIGN_EXTENDED_DEF :
		  fprintf (dump_file, "SIGN_EXTENDED_DEF, source_mode = %s\n",
			   GET_MODE_NAME (source_mode));
		  break;
		case ZERO_EXTENDED_DEF :
		  fprintf (dump_file, "ZERO_EXTENDED_DEF, source_mode = %s\n",
			   GET_MODE_NAME (source_mode));
		  break;
		case EXTENDED_DEF :
		  fprintf (dump_file, "EXTENDED_DEF, ");
		  if (source_mode != MAX_MACHINE_MODE
		      && source_mode_unsigned != MAX_MACHINE_MODE)
		    {
		      fprintf (dump_file, "positive const, ");
		      fprintf (dump_file, "source_mode_signed = %s, ",
			       GET_MODE_NAME (source_mode));
		      fprintf (dump_file, "source_mode_unsigned = %s\n",
			       GET_MODE_NAME (source_mode_unsigned));
		    }
		  else if (source_mode != MAX_MACHINE_MODE)
		    fprintf (dump_file, "source_mode_signed = %s\n",
			     GET_MODE_NAME (source_mode));
		  else
		    fprintf (dump_file, "source_mode_unsigned = %s\n",
			     GET_MODE_NAME (source_mode_unsigned));
		  break;
		default :
		  gcc_unreachable ();
		}
	    }
	}
    }
}