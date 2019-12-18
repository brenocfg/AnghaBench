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
struct dwarf2_cu {int dummy; } ;
struct die_info {int dummy; } ;
struct attribute {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DW_AT_specification ; 
 struct attribute* dwarf2_attr (struct die_info*,int /*<<< orphan*/ ,struct dwarf2_cu*) ; 
 int /*<<< orphan*/  dwarf2_get_ref_die_offset (struct attribute*,struct dwarf2_cu*) ; 
 struct die_info* follow_die_ref (int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct die_info *
die_specification (struct die_info *die, struct dwarf2_cu *cu)
{
  struct attribute *spec_attr = dwarf2_attr (die, DW_AT_specification, cu);

  if (spec_attr == NULL)
    return NULL;
  else
    return follow_die_ref (dwarf2_get_ref_die_offset (spec_attr, cu));
}