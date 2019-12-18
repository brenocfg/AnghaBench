#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct group_reloc_table_entry {scalar_t__ alu_code; } ;
typedef  int /*<<< orphan*/  parse_operand_result ;
struct TYPE_3__ {scalar_t__ type; int /*<<< orphan*/  exp; } ;
struct TYPE_4__ {TYPE_1__ reloc; int /*<<< orphan*/  error; } ;

/* Variables and functions */
 scalar_t__ FAIL ; 
 int /*<<< orphan*/  GE_NO_PREFIX ; 
 int /*<<< orphan*/  PARSE_OPERAND_FAIL ; 
 int /*<<< orphan*/  PARSE_OPERAND_FAIL_NO_BACKTRACK ; 
 int /*<<< orphan*/  PARSE_OPERAND_SUCCESS ; 
 scalar_t__ SUCCESS ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ find_group_reloc_table_entry (char**,struct group_reloc_table_entry**) ; 
 TYPE_2__ inst ; 
 scalar_t__ my_get_expression (int /*<<< orphan*/ *,char**,int /*<<< orphan*/ ) ; 
 scalar_t__ parse_shifter_operand (char**,int) ; 

__attribute__((used)) static parse_operand_result
parse_shifter_operand_group_reloc (char **str, int i)
{
  /* Determine if we have the sequence of characters #: or just :
     coming next.  If we do, then we check for a group relocation.
     If we don't, punt the whole lot to parse_shifter_operand.  */

  if (((*str)[0] == '#' && (*str)[1] == ':')
      || (*str)[0] == ':')
    {
      struct group_reloc_table_entry *entry;

      if ((*str)[0] == '#')
        (*str) += 2;
      else
        (*str)++;

      /* Try to parse a group relocation.  Anything else is an error.  */
      if (find_group_reloc_table_entry (str, &entry) == FAIL)
        {
          inst.error = _("unknown group relocation");
          return PARSE_OPERAND_FAIL_NO_BACKTRACK;
        }

      /* We now have the group relocation table entry corresponding to
         the name in the assembler source.  Next, we parse the expression.  */
      if (my_get_expression (&inst.reloc.exp, str, GE_NO_PREFIX))
        return PARSE_OPERAND_FAIL_NO_BACKTRACK;

      /* Record the relocation type (always the ALU variant here).  */
      inst.reloc.type = entry->alu_code;
      assert (inst.reloc.type != 0);

      return PARSE_OPERAND_SUCCESS;
    }
  else
    return parse_shifter_operand (str, i) == SUCCESS
           ? PARSE_OPERAND_SUCCESS : PARSE_OPERAND_FAIL;

  /* Never reached.  */
}