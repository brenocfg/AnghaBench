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
struct df {int dummy; } ;
typedef  int /*<<< orphan*/  rtx ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int DF_INSN_LUID (struct df*,int /*<<< orphan*/ ) ; 
 scalar_t__ DF_INSN_UID_DEFS (struct df*,unsigned int) ; 
 scalar_t__ DF_INSN_UID_USES (struct df*,unsigned int) ; 
 int DF_REF_BBNO (scalar_t__) ; 
 unsigned int INSN_UID (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  df_regs_chain_dump (struct df*,scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,...) ; 

void
df_insn_debug_regno (struct df *df, rtx insn, FILE *file)
{
  unsigned int uid;
  int bbi;

  uid = INSN_UID (insn);
  if (DF_INSN_UID_DEFS (df, uid))
    bbi = DF_REF_BBNO (DF_INSN_UID_DEFS (df, uid));
  else if (DF_INSN_UID_USES(df, uid))
    bbi = DF_REF_BBNO (DF_INSN_UID_USES (df, uid));
  else
    bbi = -1;

  fprintf (file, "insn %d bb %d luid %d defs ",
	   uid, bbi, DF_INSN_LUID (df, insn));
  df_regs_chain_dump (df, DF_INSN_UID_DEFS (df, uid), file);
    
  fprintf (file, " uses ");
  df_regs_chain_dump (df, DF_INSN_UID_USES (df, uid), file);
  fprintf (file, "\n");
}