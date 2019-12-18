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
 int /*<<< orphan*/  ASM_DECLARE_OBJECT_NAME (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ASM_OUTPUT_LABEL (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  DECL_ALIGN (int /*<<< orphan*/ ) ; 
 scalar_t__ DECL_INITIAL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DECL_SIZE_UNIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  asm_out_file ; 
 int /*<<< orphan*/  assemble_zeros (int /*<<< orphan*/ ) ; 
 scalar_t__ error_mark_node ; 
 int /*<<< orphan*/  initializer_zerop (scalar_t__) ; 
 int /*<<< orphan*/  last_assemble_variable_decl ; 
 int /*<<< orphan*/  output_constant (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tree_low_cst (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
assemble_variable_contents (tree decl, const char *name,
			    bool dont_output_data)
{
  /* Do any machine/system dependent processing of the object.  */
#ifdef ASM_DECLARE_OBJECT_NAME
  last_assemble_variable_decl = decl;
  ASM_DECLARE_OBJECT_NAME (asm_out_file, name, decl);
#else
  /* Standard thing is just output label for the object.  */
  ASM_OUTPUT_LABEL (asm_out_file, name);
#endif /* ASM_DECLARE_OBJECT_NAME */

  if (!dont_output_data)
    {
      if (DECL_INITIAL (decl)
	  && DECL_INITIAL (decl) != error_mark_node
	  && !initializer_zerop (DECL_INITIAL (decl)))
	/* Output the actual data.  */
	output_constant (DECL_INITIAL (decl),
			 tree_low_cst (DECL_SIZE_UNIT (decl), 1),
			 DECL_ALIGN (decl));
      else
	/* Leave space for it.  */
	assemble_zeros (tree_low_cst (DECL_SIZE_UNIT (decl), 1));
    }
}