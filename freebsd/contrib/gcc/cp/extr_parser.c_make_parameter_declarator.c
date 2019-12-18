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
typedef  int /*<<< orphan*/  tree ;
struct TYPE_3__ {int ellipsis_p; int /*<<< orphan*/  default_argument; int /*<<< orphan*/ * declarator; int /*<<< orphan*/  decl_specifiers; int /*<<< orphan*/ * next; } ;
typedef  TYPE_1__ cp_parameter_declarator ;
typedef  int /*<<< orphan*/  cp_declarator ;
typedef  int /*<<< orphan*/  cp_decl_specifier_seq ;

/* Variables and functions */
 scalar_t__ alloc_declarator (int) ; 
 int /*<<< orphan*/  clear_decl_specs (int /*<<< orphan*/ *) ; 

cp_parameter_declarator *
make_parameter_declarator (cp_decl_specifier_seq *decl_specifiers,
			   cp_declarator *declarator,
			   tree default_argument)
{
  cp_parameter_declarator *parameter;

  parameter = ((cp_parameter_declarator *)
	       alloc_declarator (sizeof (cp_parameter_declarator)));
  parameter->next = NULL;
  if (decl_specifiers)
    parameter->decl_specifiers = *decl_specifiers;
  else
    clear_decl_specs (&parameter->decl_specifiers);
  parameter->declarator = declarator;
  parameter->default_argument = default_argument;
  parameter->ellipsis_p = false;

  return parameter;
}