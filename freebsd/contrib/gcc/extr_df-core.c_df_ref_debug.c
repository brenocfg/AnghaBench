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
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int DF_REF_BBNO (struct df_ref*) ; 
 int /*<<< orphan*/  DF_REF_CHAIN (struct df_ref*) ; 
 int DF_REF_FLAGS (struct df_ref*) ; 
 int /*<<< orphan*/  DF_REF_ID (struct df_ref*) ; 
 scalar_t__ DF_REF_INSN (struct df_ref*) ; 
 int DF_REF_REGNO (struct df_ref*) ; 
 scalar_t__ DF_REF_REG_DEF_P (struct df_ref*) ; 
 int INSN_UID (scalar_t__) ; 
 int /*<<< orphan*/  df_chain_dump (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,...) ; 

void
df_ref_debug (struct df_ref *ref, FILE *file)
{
  fprintf (file, "%c%d ",
	   DF_REF_REG_DEF_P (ref) ? 'd' : 'u',
	   DF_REF_ID (ref));
  fprintf (file, "reg %d bb %d insn %d flag %x chain ",
	   DF_REF_REGNO (ref),
	   DF_REF_BBNO (ref),
	   DF_REF_INSN (ref) ? INSN_UID (DF_REF_INSN (ref)) : -1,
	   DF_REF_FLAGS (ref));
  df_chain_dump (DF_REF_CHAIN (ref), file);
  fprintf (file, "\n");
}