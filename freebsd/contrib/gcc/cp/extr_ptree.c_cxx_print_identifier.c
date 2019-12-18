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
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  IDENTIFIER_BINDING (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IDENTIFIER_LABEL_VALUE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IDENTIFIER_NAMESPACE_BINDINGS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IDENTIFIER_TEMPLATE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cxx_print_binding (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  indent_to (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  print_node (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int) ; 

void
cxx_print_identifier (FILE *file, tree node, int indent)
{
  if (indent == 0)
    fprintf (file, " ");
  else
    indent_to (file, indent);
  cxx_print_binding (file, IDENTIFIER_NAMESPACE_BINDINGS (node), "bindings");
  if (indent == 0)
    fprintf (file, " ");
  else
    indent_to (file, indent);
  cxx_print_binding (file, IDENTIFIER_BINDING (node), "local bindings");
  print_node (file, "label", IDENTIFIER_LABEL_VALUE (node), indent + 4);
  print_node (file, "template", IDENTIFIER_TEMPLATE (node), indent + 4);
}