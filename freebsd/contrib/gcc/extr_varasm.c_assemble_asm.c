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
typedef  int /*<<< orphan*/  tree ;

/* Variables and functions */
 scalar_t__ ADDR_EXPR ; 
 scalar_t__ TREE_CODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TREE_OPERAND (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char* TREE_STRING_POINTER (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  app_enable () ; 
 int /*<<< orphan*/  asm_out_file ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*) ; 

void
assemble_asm (tree string)
{
  app_enable ();

  if (TREE_CODE (string) == ADDR_EXPR)
    string = TREE_OPERAND (string, 0);

  fprintf (asm_out_file, "\t%s\n", TREE_STRING_POINTER (string));
}