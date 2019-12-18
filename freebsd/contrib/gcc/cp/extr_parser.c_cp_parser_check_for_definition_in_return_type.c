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
struct TYPE_3__ {scalar_t__ kind; struct TYPE_3__* declarator; } ;
typedef  TYPE_1__ cp_declarator ;

/* Variables and functions */
 scalar_t__ cdk_function ; 
 scalar_t__ cdk_pointer ; 
 scalar_t__ cdk_ptrmem ; 
 scalar_t__ cdk_reference ; 
 int /*<<< orphan*/  error (char*) ; 
 int /*<<< orphan*/  inform (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
cp_parser_check_for_definition_in_return_type (cp_declarator *declarator,
					       tree type)
{
  /* [dcl.fct] forbids type definitions in return types.
     Unfortunately, it's not easy to know whether or not we are
     processing a return type until after the fact.  */
  while (declarator
	 && (declarator->kind == cdk_pointer
	     || declarator->kind == cdk_reference
	     || declarator->kind == cdk_ptrmem))
    declarator = declarator->declarator;
  if (declarator
      && declarator->kind == cdk_function)
    {
      error ("new types may not be defined in a return type");
      inform ("(perhaps a semicolon is missing after the definition of %qT)",
	      type);
    }
}