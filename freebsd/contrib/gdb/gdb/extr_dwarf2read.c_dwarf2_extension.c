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
 int /*<<< orphan*/  DW_AT_extension ; 
 struct attribute* dwarf2_attr (struct die_info*,int /*<<< orphan*/ ,struct dwarf2_cu*) ; 
 unsigned int dwarf2_get_ref_die_offset (struct attribute*,struct dwarf2_cu*) ; 
 int /*<<< orphan*/  error (char*,unsigned int) ; 
 struct die_info* follow_die_ref (unsigned int) ; 

__attribute__((used)) static struct die_info *
dwarf2_extension (struct die_info *die, struct dwarf2_cu *cu)
{
  struct attribute *attr;
  struct die_info *extension_die;
  unsigned int ref;

  attr = dwarf2_attr (die, DW_AT_extension, cu);
  if (attr == NULL)
    return NULL;

  ref = dwarf2_get_ref_die_offset (attr, cu);
  extension_die = follow_die_ref (ref);
  if (!extension_die)
    {
      error ("Dwarf Error: Cannot find referent at offset %d.", ref);
    }

  return extension_die;
}