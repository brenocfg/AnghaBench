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
struct df_link {int /*<<< orphan*/  ref; struct df_link* next; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int DF_REF_BBNO (int /*<<< orphan*/ ) ; 
 int DF_REF_ID (int /*<<< orphan*/ ) ; 
 scalar_t__ DF_REF_INSN (int /*<<< orphan*/ ) ; 
 int DF_REF_INSN_UID (int /*<<< orphan*/ ) ; 
 scalar_t__ DF_REF_REG_DEF_P (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,...) ; 

void
df_chain_dump (struct df_link *link, FILE *file)
{
  fprintf (file, "{ ");
  for (; link; link = link->next)
    {
      fprintf (file, "%c%d(bb %d insn %d) ",
	       DF_REF_REG_DEF_P (link->ref) ? 'd' : 'u',
	       DF_REF_ID (link->ref),
	       DF_REF_BBNO (link->ref),
	       DF_REF_INSN (link->ref) ? DF_REF_INSN_UID (link->ref) : -1);
    }
  fprintf (file, "}");
}