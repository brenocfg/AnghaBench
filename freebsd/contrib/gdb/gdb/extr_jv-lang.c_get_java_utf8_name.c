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
struct value {int dummy; } ;
struct obstack {int dummy; } ;
typedef  scalar_t__ CORE_ADDR ;

/* Variables and functions */
 scalar_t__ TYPE_LENGTH (int /*<<< orphan*/ ) ; 
 scalar_t__ VALUE_ADDRESS (struct value*) ; 
 scalar_t__ VALUE_OFFSET (struct value*) ; 
 int /*<<< orphan*/  VALUE_TYPE (struct value*) ; 
 char* obstack_alloc (struct obstack*,int) ; 
 int /*<<< orphan*/  read_memory (scalar_t__,char*,int) ; 
 scalar_t__ value_as_long (struct value*) ; 
 struct value* value_struct_elt (struct value**,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,char*) ; 

char *
get_java_utf8_name (struct obstack *obstack, struct value *name)
{
  char *chrs;
  struct value *temp = name;
  int name_length;
  CORE_ADDR data_addr;
  temp = value_struct_elt (&temp, NULL, "length", NULL, "structure");
  name_length = (int) value_as_long (temp);
  data_addr = VALUE_ADDRESS (temp) + VALUE_OFFSET (temp)
    + TYPE_LENGTH (VALUE_TYPE (temp));
  chrs = obstack_alloc (obstack, name_length + 1);
  chrs[name_length] = '\0';
  read_memory (data_addr, chrs, name_length);
  return chrs;
}