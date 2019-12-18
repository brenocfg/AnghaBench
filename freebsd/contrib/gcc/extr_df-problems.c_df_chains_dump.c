#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct df_ref {int flags; } ;
struct TYPE_4__ {unsigned int bitmap_size; } ;
struct TYPE_3__ {unsigned int bitmap_size; } ;
struct df {TYPE_2__ use_info; TYPE_1__ def_info; } ;
struct dataflow {int flags; struct df* df; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 struct df_ref* DF_DEFS_GET (struct df*,unsigned int) ; 
 int DF_DU_CHAIN ; 
 int DF_INSN_LUID (struct df*,scalar_t__) ; 
 int DF_REF_BBNO (struct df_ref*) ; 
 int /*<<< orphan*/  DF_REF_CHAIN (struct df_ref*) ; 
 scalar_t__ DF_REF_INSN (struct df_ref*) ; 
 int DF_REF_INSN_UID (struct df_ref*) ; 
 int DF_REF_IN_NOTE ; 
 int DF_REF_READ_WRITE ; 
 int DF_REF_REGNO (struct df_ref*) ; 
 int DF_REF_STRIPPED ; 
 int DF_UD_CHAIN ; 
 struct df_ref* DF_USES_GET (struct df*,unsigned int) ; 
 int /*<<< orphan*/  df_chain_dump (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,...) ; 

__attribute__((used)) static void
df_chains_dump (struct dataflow *dflow, FILE *file)
{
  struct df *df = dflow->df;
  unsigned int j;

  if (dflow->flags & DF_DU_CHAIN)
    {
      fprintf (file, "Def-use chains:\n");
      for (j = 0; j < df->def_info.bitmap_size; j++)
	{
	  struct df_ref *def = DF_DEFS_GET (df, j);
	  if (def)
	    {
	      fprintf (file, "d%d bb %d luid %d insn %d reg %d ",
		       j, DF_REF_BBNO (def),
		       DF_REF_INSN (def) ? 
		       DF_INSN_LUID (df, DF_REF_INSN (def)):
		       -1,
		       DF_REF_INSN (def) ? DF_REF_INSN_UID (def) : -1,
		       DF_REF_REGNO (def));
	      if (def->flags & DF_REF_READ_WRITE)
		fprintf (file, "read/write ");
	      df_chain_dump (DF_REF_CHAIN (def), file);
	      fprintf (file, "\n");
	    }
	}
    }

  if (dflow->flags & DF_UD_CHAIN)
    {
      fprintf (file, "Use-def chains:\n");
      for (j = 0; j < df->use_info.bitmap_size; j++)
	{
	  struct df_ref *use = DF_USES_GET (df, j);
	  if (use)
	    {
	      fprintf (file, "u%d bb %d luid %d insn %d reg %d ",
		       j, DF_REF_BBNO (use),
		       DF_REF_INSN (use) ? 
		       DF_INSN_LUID (df, DF_REF_INSN (use))
		       : -1,
		       DF_REF_INSN (DF_USES_GET (df, j)) ?
		       DF_REF_INSN_UID (DF_USES_GET (df,j))
		       : -1,
		       DF_REF_REGNO (use));
	      if (use->flags & DF_REF_READ_WRITE)
		fprintf (file, "read/write ");
	      if (use->flags & DF_REF_STRIPPED)
		fprintf (file, "stripped ");
	      if (use->flags & DF_REF_IN_NOTE)
		fprintf (file, "note ");
	      df_chain_dump (DF_REF_CHAIN (use), file);
	      fprintf (file, "\n");
	    }
	}
    }
}