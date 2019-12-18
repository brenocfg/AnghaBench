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
typedef  enum darwin_section_enum { ____Placeholder_darwin_section_enum } darwin_section_enum ;

/* Variables and functions */
 size_t ARRAY_SIZE (int const*) ; 
 int /*<<< orphan*/ * darwin_sections ; 
#define  objc_cat_cls_meth_section 147 
#define  objc_cat_inst_meth_section 146 
#define  objc_category_section 145 
#define  objc_class_names_section 144 
#define  objc_class_section 143 
#define  objc_class_vars_section 142 
#define  objc_cls_meth_section 141 
#define  objc_cls_refs_section 140 
#define  objc_constant_string_object_section 139 
#define  objc_inst_meth_section 138 
#define  objc_instance_vars_section 137 
#define  objc_meta_class_section 136 
#define  objc_meth_var_names_section 135 
#define  objc_meth_var_types_section 134 
#define  objc_module_info_section 133 
#define  objc_protocol_section 132 
#define  objc_selector_fixup_section 131 
#define  objc_selector_refs_section 130 
#define  objc_string_object_section 129 
#define  objc_symbols_section 128 
 int /*<<< orphan*/  output_section_asm_op (void const*) ; 
 int /*<<< orphan*/  switch_to_section (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
output_objc_section_asm_op (const void *directive)
{
  static bool been_here = false;

  if (! been_here)
    {
      static const enum darwin_section_enum tomark[] =
	{
	  /* written, cold -> hot */
	  objc_cat_cls_meth_section,
	  objc_cat_inst_meth_section,
	  objc_string_object_section,
	  objc_constant_string_object_section,
	  objc_selector_refs_section,
	  objc_selector_fixup_section,
	  objc_cls_refs_section,
	  objc_class_section,
	  objc_meta_class_section,
	  /* shared, hot -> cold */
	  objc_cls_meth_section,
	  objc_inst_meth_section,
	  objc_protocol_section,
	  objc_class_names_section,
	  objc_meth_var_types_section,
	  objc_meth_var_names_section,
	  objc_category_section,
	  objc_class_vars_section,
	  objc_instance_vars_section,
	  objc_module_info_section,
	  objc_symbols_section
	};
      size_t i;

      been_here = true;
      for (i = 0; i < ARRAY_SIZE (tomark); i++)
	switch_to_section (darwin_sections[tomark[i]]);
    }
  output_section_asm_op (directive);
}