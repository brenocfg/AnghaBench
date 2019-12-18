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
struct arc_operand_value {scalar_t__ type; int /*<<< orphan*/  name; } ;
struct arc_ext_operand_value {struct arc_ext_operand_value* next; struct arc_operand_value operand; } ;

/* Variables and functions */
 scalar_t__ COND ; 
 struct arc_ext_operand_value* arc_ext_operands ; 
 int /*<<< orphan*/  strcmp (char*,int /*<<< orphan*/ ) ; 

struct arc_operand_value *
get_ext_suffix (char *s)
{
  struct arc_ext_operand_value *suffix = arc_ext_operands;

  while (suffix)
    {
      if ((COND == suffix->operand.type)
	  && !strcmp(s,suffix->operand.name))
	return(&suffix->operand);
      suffix = suffix->next;
    }
  return NULL;
}