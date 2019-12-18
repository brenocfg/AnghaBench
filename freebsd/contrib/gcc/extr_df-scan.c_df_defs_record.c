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
struct dataflow {int dummy; } ;
typedef  int /*<<< orphan*/  rtx ;
typedef  int /*<<< orphan*/  basic_block ;
typedef  scalar_t__ RTX_CODE ;

/* Variables and functions */
 scalar_t__ CLOBBER ; 
 scalar_t__ COND_EXEC ; 
 int /*<<< orphan*/  COND_EXEC_CODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DF_REF_MUST_CLOBBER ; 
 scalar_t__ GET_CODE (int /*<<< orphan*/ ) ; 
 scalar_t__ PARALLEL ; 
 scalar_t__ SET ; 
 int /*<<< orphan*/  XVECEXP (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int XVECLEN (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  df_def_record_1 (struct dataflow*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
df_defs_record (struct dataflow *dflow, rtx x, basic_block bb, rtx insn)
{
  RTX_CODE code = GET_CODE (x);

  if (code == SET || code == CLOBBER)
    {
      /* Mark the single def within the pattern.  */
      df_def_record_1 (dflow, x, bb, insn, 
		       code == CLOBBER ? DF_REF_MUST_CLOBBER : 0, true);
    }
  else if (code == COND_EXEC)
    {
      df_defs_record  (dflow, COND_EXEC_CODE (x), bb, insn);
    }
  else if (code == PARALLEL)
    {
      int i;

      /* Mark the multiple defs within the pattern.  */
      for (i = XVECLEN (x, 0) - 1; i >= 0; i--)
	 df_defs_record (dflow, XVECEXP (x, 0, i), bb, insn);
    }
}