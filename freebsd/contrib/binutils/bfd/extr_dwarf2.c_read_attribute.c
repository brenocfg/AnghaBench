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
struct comp_unit {int dummy; } ;
struct attribute {int /*<<< orphan*/  name; } ;
struct attr_abbrev {int /*<<< orphan*/  form; int /*<<< orphan*/  name; } ;
typedef  int /*<<< orphan*/  bfd_byte ;

/* Variables and functions */
 int /*<<< orphan*/ * read_attribute_value (struct attribute*,int /*<<< orphan*/ ,struct comp_unit*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static bfd_byte *
read_attribute (struct attribute *attr,
		struct attr_abbrev *abbrev,
		struct comp_unit *unit,
		bfd_byte *info_ptr)
{
  attr->name = abbrev->name;
  info_ptr = read_attribute_value (attr, abbrev->form, unit, info_ptr);
  return info_ptr;
}