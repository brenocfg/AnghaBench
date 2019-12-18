#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  reg_entry ;
struct TYPE_3__ {int /*<<< orphan*/  const* X_add_number; int /*<<< orphan*/  X_op; } ;
typedef  TYPE_1__ expressionS ;

/* Variables and functions */
 int /*<<< orphan*/  O_register ; 
 int i386_regtab ; 
 char* input_line_pointer ; 
 int /*<<< orphan*/ * parse_register (char*,char**) ; 

int
i386_parse_name (char *name, expressionS *e, char *nextcharP)
{
  const reg_entry *r;
  char *end = input_line_pointer;

  *end = *nextcharP;
  r = parse_register (name, &input_line_pointer);
  if (r && end <= input_line_pointer)
    {
      *nextcharP = *input_line_pointer;
      *input_line_pointer = 0;
      e->X_op = O_register;
      e->X_add_number = r - i386_regtab;
      return 1;
    }
  input_line_pointer = end;
  *end = 0;
  return 0;
}