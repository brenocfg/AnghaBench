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
typedef  scalar_t__ tree ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 scalar_t__ C_IS_RESERVED_WORD (scalar_t__) ; 
 size_t C_RID_CODE (scalar_t__) ; 
 char* IDENTIFIER_POINTER (scalar_t__) ; 
 int /*<<< orphan*/  I_LABEL_DECL (scalar_t__) ; 
 int /*<<< orphan*/  I_SYMBOL_DECL (scalar_t__) ; 
 int /*<<< orphan*/  I_TAG_DECL (scalar_t__) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,void*,char*) ; 
 int /*<<< orphan*/  indent_to (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  print_node (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int) ; 
 scalar_t__* ridpointers ; 

void
c_print_identifier (FILE *file, tree node, int indent)
{
  print_node (file, "symbol", I_SYMBOL_DECL (node), indent + 4);
  print_node (file, "tag", I_TAG_DECL (node), indent + 4);
  print_node (file, "label", I_LABEL_DECL (node), indent + 4);
  if (C_IS_RESERVED_WORD (node))
    {
      tree rid = ridpointers[C_RID_CODE (node)];
      indent_to (file, indent + 4);
      fprintf (file, "rid %p \"%s\"",
	       (void *) rid, IDENTIFIER_POINTER (rid));
    }
}