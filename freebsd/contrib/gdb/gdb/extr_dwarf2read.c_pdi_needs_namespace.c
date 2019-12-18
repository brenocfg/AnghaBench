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
typedef  enum dwarf_tag { ____Placeholder_dwarf_tag } dwarf_tag ;

/* Variables and functions */
#define  DW_TAG_class_type 133 
#define  DW_TAG_enumeration_type 132 
#define  DW_TAG_enumerator 131 
#define  DW_TAG_structure_type 130 
#define  DW_TAG_typedef 129 
#define  DW_TAG_union_type 128 

__attribute__((used)) static int
pdi_needs_namespace (enum dwarf_tag tag, const char *namespace)
{
  if (namespace == NULL || namespace[0] == '\0')
    return 0;

  switch (tag)
    {
    case DW_TAG_typedef:
    case DW_TAG_class_type:
    case DW_TAG_structure_type:
    case DW_TAG_union_type:
    case DW_TAG_enumeration_type:
    case DW_TAG_enumerator:
      return 1;
    default:
      return 0;
    }
}