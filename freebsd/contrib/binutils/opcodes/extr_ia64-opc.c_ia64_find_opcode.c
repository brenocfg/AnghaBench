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
struct ia64_opcode {int dummy; } ;

/* Variables and functions */
 short find_main_ent (short) ; 
 short find_string_ent (char*) ; 
 int /*<<< orphan*/  get_opc_prefix (char const**,char*) ; 
 struct ia64_opcode* ia64_find_matching_opcode (char const*,short) ; 
 int strlen (char const*) ; 

struct ia64_opcode *
ia64_find_opcode (const char *name)
{
  char op[129];
  const char *suffix;
  short place;
  short name_index;

  if (strlen (name) > 128)
    {
      return NULL;
    }
  suffix = name;
  get_opc_prefix (&suffix, op);
  name_index = find_string_ent (op);
  if (name_index < 0)
    {
      return NULL;
    }

  place = find_main_ent (name_index);

  if (place < 0)
    {
      return NULL;
    }
  return ia64_find_matching_opcode (name, place);
}