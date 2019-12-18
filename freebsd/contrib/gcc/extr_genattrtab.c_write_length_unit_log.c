#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct insn_ent {struct insn_ent* next; } ;
struct attr_value {int /*<<< orphan*/  value; struct insn_ent* first_insn; struct attr_value* next; } ;
struct attr_desc {struct attr_value* first_value; TYPE_1__* default_val; } ;
struct TYPE_2__ {int /*<<< orphan*/  value; } ;

/* Variables and functions */
 struct attr_desc* find_attr (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  length_str ; 
 unsigned int or_attr_value (int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  printf (char*,unsigned int) ; 

__attribute__((used)) static void
write_length_unit_log (void)
{
  struct attr_desc *length_attr = find_attr (&length_str, 0);
  struct attr_value *av;
  struct insn_ent *ie;
  unsigned int length_unit_log, length_or;
  int unknown = 0;

  if (length_attr == 0)
    return;
  length_or = or_attr_value (length_attr->default_val->value, &unknown);
  for (av = length_attr->first_value; av; av = av->next)
    for (ie = av->first_insn; ie; ie = ie->next)
      length_or |= or_attr_value (av->value, &unknown);

  if (unknown)
    length_unit_log = 0;
  else
    {
      length_or = ~length_or;
      for (length_unit_log = 0; length_or & 1; length_or >>= 1)
	length_unit_log++;
    }
  printf ("const int length_unit_log = %u;\n", length_unit_log);
}