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
struct symbol {int dummy; } ;
struct dwarf2_cu {int dummy; } ;
struct die_info {scalar_t__ tag; struct die_info* child; } ;
struct attribute {scalar_t__ form; } ;
typedef  scalar_t__ SYMBOL_VALUE_ADDRESS ;
typedef  scalar_t__ CORE_ADDR ;

/* Variables and functions */
 int /*<<< orphan*/  DW_AT_data_member_location ; 
 int /*<<< orphan*/  DW_AT_location ; 
 int /*<<< orphan*/  DW_BLOCK (struct attribute*) ; 
 scalar_t__ DW_FORM_data4 ; 
 scalar_t__ DW_FORM_data8 ; 
 int /*<<< orphan*/  add_symbol_to_list (scalar_t__,int /*<<< orphan*/ *) ; 
 scalar_t__ attr_form_is_block (struct attribute*) ; 
 scalar_t__ decode_locdesc (int /*<<< orphan*/ ,struct dwarf2_cu*) ; 
 struct attribute* dwarf2_attr (struct die_info*,int /*<<< orphan*/ ,struct dwarf2_cu*) ; 
 int /*<<< orphan*/  dwarf2_complex_location_expr_complaint () ; 
 int /*<<< orphan*/  dwarf2_invalid_attrib_class_complaint (char*,char*) ; 
 int /*<<< orphan*/  global_symbols ; 
 struct symbol* new_symbol (struct die_info*,int /*<<< orphan*/ *,struct dwarf2_cu*) ; 
 struct die_info* sibling_die (struct die_info*) ; 

__attribute__((used)) static void
read_common_block (struct die_info *die, struct dwarf2_cu *cu)
{
  struct die_info *child_die;
  struct attribute *attr;
  struct symbol *sym;
  CORE_ADDR base = (CORE_ADDR) 0;

  attr = dwarf2_attr (die, DW_AT_location, cu);
  if (attr)
    {
      /* Support the .debug_loc offsets */
      if (attr_form_is_block (attr))
        {
          base = decode_locdesc (DW_BLOCK (attr), cu);
        }
      else if (attr->form == DW_FORM_data4 || attr->form == DW_FORM_data8)
        {
	  dwarf2_complex_location_expr_complaint ();
        }
      else
        {
	  dwarf2_invalid_attrib_class_complaint ("DW_AT_location",
						 "common block member");
        }
    }
  if (die->child != NULL)
    {
      child_die = die->child;
      while (child_die && child_die->tag)
	{
	  sym = new_symbol (child_die, NULL, cu);
	  attr = dwarf2_attr (child_die, DW_AT_data_member_location, cu);
	  if (attr)
	    {
	      SYMBOL_VALUE_ADDRESS (sym) =
		base + decode_locdesc (DW_BLOCK (attr), cu);
	      add_symbol_to_list (sym, &global_symbols);
	    }
	  child_die = sibling_die (child_die);
	}
    }
}