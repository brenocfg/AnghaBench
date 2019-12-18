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
struct df_ref {int dummy; } ;
typedef  scalar_t__ rtx ;

/* Variables and functions */
 int /*<<< orphan*/  DF_REF_INSN (struct df_ref*) ; 
 scalar_t__* DF_REF_REAL_LOC (struct df_ref*) ; 
 scalar_t__ DF_REF_REAL_REG (struct df_ref*) ; 
 int INSN_UID (int /*<<< orphan*/ ) ; 
 int REGNO (scalar_t__) ; 
 scalar_t__ dump_file ; 
 int /*<<< orphan*/  fprintf (scalar_t__,char*,int,int,int) ; 

__attribute__((used)) static void
replace_ref (struct df_ref *ref, rtx reg)
{
  rtx oldreg = DF_REF_REAL_REG (ref);
  rtx *loc = DF_REF_REAL_LOC (ref);

  if (oldreg == reg)
    return;
  if (dump_file)
    fprintf (dump_file, "Updating insn %i (%i->%i)\n",
	     INSN_UID (DF_REF_INSN (ref)), REGNO (oldreg), REGNO (reg)); 
  *loc = reg;
}