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
struct df_ref {struct df_ref* next_ref; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  DF_REF_CHAIN (struct df_ref*) ; 
 int DF_REF_ID (struct df_ref*) ; 
 int /*<<< orphan*/  DF_REF_REGNO (struct df_ref*) ; 
 scalar_t__ DF_REF_REG_DEF_P (struct df_ref*) ; 
 int /*<<< orphan*/  df_chain_dump (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,...) ; 

void
df_refs_chain_dump (struct df_ref *ref, bool follow_chain, FILE *file)
{
  fprintf (file, "{ ");
  while (ref)
    {
      fprintf (file, "%c%d(%d) ",
	       DF_REF_REG_DEF_P (ref) ? 'd' : 'u',
	       DF_REF_ID (ref),
	       DF_REF_REGNO (ref));
      if (follow_chain)
	df_chain_dump (DF_REF_CHAIN (ref), file);
      ref = ref->next_ref;
    }
  fprintf (file, "}");
}