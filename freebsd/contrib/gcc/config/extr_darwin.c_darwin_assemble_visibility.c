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

/* Variables and functions */
 int /*<<< orphan*/  DECL_ASSEMBLER_NAME (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IDENTIFIER_POINTER (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OPT_Wattributes ; 
 int VISIBILITY_DEFAULT ; 
 int VISIBILITY_HIDDEN ; 
 int /*<<< orphan*/  asm_out_file ; 
 int /*<<< orphan*/  assemble_name (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fputs (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  warning (int /*<<< orphan*/ ,char*) ; 

void
darwin_assemble_visibility (tree decl, int vis)
{
  if (vis == VISIBILITY_DEFAULT)
    ;
  else if (vis == VISIBILITY_HIDDEN)
    {
      fputs ("\t.private_extern ", asm_out_file);
      assemble_name (asm_out_file,
		     (IDENTIFIER_POINTER (DECL_ASSEMBLER_NAME (decl))));
      fputs ("\n", asm_out_file);
    }
  else
    warning (OPT_Wattributes, "internal and protected visibility attributes "
	     "not supported in this configuration; ignored");
}