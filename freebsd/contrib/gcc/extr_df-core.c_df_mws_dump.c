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
struct df_mw_hardreg {scalar_t__ type; struct df_mw_hardreg* next; struct df_link* regs; } ;
struct df_link {struct df_link* next; int /*<<< orphan*/  ref; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int DF_REF_REGNO (int /*<<< orphan*/ ) ; 
 scalar_t__ DF_REF_REG_DEF ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,...) ; 

__attribute__((used)) static void
df_mws_dump (struct df_mw_hardreg *mws, FILE *file)
{
  while (mws)
    {
      struct df_link *regs = mws->regs;
      fprintf (file, "%c%d(", 
	       (mws->type == DF_REF_REG_DEF) ? 'd' : 'u',
	       DF_REF_REGNO (regs->ref));
      while (regs)
	{
	  fprintf (file, "%d ", DF_REF_REGNO (regs->ref));
	  regs = regs->next;
	}

      fprintf (file, ") "); 
      mws = mws->next;
    }
}