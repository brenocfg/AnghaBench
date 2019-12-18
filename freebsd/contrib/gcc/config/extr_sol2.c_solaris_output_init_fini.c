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
typedef  int /*<<< orphan*/  tree ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  ASM_OUTPUT_CALL (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DECL_ATTRIBUTES (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ lookup_attribute (char*,int /*<<< orphan*/ ) ; 

void
solaris_output_init_fini (FILE *file, tree decl)
{
  if (lookup_attribute ("init", DECL_ATTRIBUTES (decl)))
    {
      fprintf (file, "\t.pushsection\t\".init\"\n");
      ASM_OUTPUT_CALL (file, decl);
      fprintf (file, "\t.popsection\n");
    }

  if (lookup_attribute ("fini", DECL_ATTRIBUTES (decl)))
    {
      fprintf (file, "\t.pushsection\t\".fini\"\n");
      ASM_OUTPUT_CALL (file, decl);
      fprintf (file, "\t.popsection\n");
    }
}