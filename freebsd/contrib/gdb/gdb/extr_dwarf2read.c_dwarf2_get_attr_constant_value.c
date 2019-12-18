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
struct attribute {scalar_t__ form; } ;

/* Variables and functions */
 scalar_t__ DW_FORM_data1 ; 
 scalar_t__ DW_FORM_data2 ; 
 scalar_t__ DW_FORM_data4 ; 
 scalar_t__ DW_FORM_data8 ; 
 scalar_t__ DW_FORM_sdata ; 
 scalar_t__ DW_FORM_udata ; 
 int DW_SND (struct attribute*) ; 
 int DW_UNSND (struct attribute*) ; 
 int /*<<< orphan*/  complaint (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dwarf_form_name (scalar_t__) ; 
 int /*<<< orphan*/  symfile_complaints ; 

__attribute__((used)) static int
dwarf2_get_attr_constant_value (struct attribute *attr, int default_value)
{
  if (attr->form == DW_FORM_sdata)
    return DW_SND (attr);
  else if (attr->form == DW_FORM_udata
           || attr->form == DW_FORM_data1
           || attr->form == DW_FORM_data2
           || attr->form == DW_FORM_data4
           || attr->form == DW_FORM_data8)
    return DW_UNSND (attr);
  else
    {
      complaint (&symfile_complaints, "Attribute value is not a constant (%s)",
                 dwarf_form_name (attr->form));
      return default_value;
    }
}