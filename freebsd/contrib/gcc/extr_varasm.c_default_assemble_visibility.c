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
 char* IDENTIFIER_POINTER (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OPT_Wattributes ; 
 int /*<<< orphan*/  asm_out_file ; 
 int /*<<< orphan*/  assemble_name (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  warning (int /*<<< orphan*/ ,char*) ; 

void
default_assemble_visibility (tree decl, int vis)
{
  static const char * const visibility_types[] = {
    NULL, "protected", "hidden", "internal"
  };

  const char *name, *type;

  name = IDENTIFIER_POINTER (DECL_ASSEMBLER_NAME (decl));
  type = visibility_types[vis];

#ifdef HAVE_GAS_HIDDEN
  fprintf (asm_out_file, "\t.%s\t", type);
  assemble_name (asm_out_file, name);
  fprintf (asm_out_file, "\n");
#else
  warning (OPT_Wattributes, "visibility attribute not supported "
	   "in this configuration; ignored");
#endif
}