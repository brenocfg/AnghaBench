#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tree ;
typedef  int /*<<< orphan*/  cp_parameter_declarator ;
struct TYPE_7__ {int /*<<< orphan*/  exception_specification; int /*<<< orphan*/  qualifiers; int /*<<< orphan*/ * parameters; } ;
struct TYPE_8__ {TYPE_1__ function; } ;
struct TYPE_9__ {TYPE_2__ u; struct TYPE_9__* declarator; } ;
typedef  TYPE_3__ cp_declarator ;
typedef  int /*<<< orphan*/  cp_cv_quals ;

/* Variables and functions */
 int /*<<< orphan*/  cdk_function ; 
 TYPE_3__* make_declarator (int /*<<< orphan*/ ) ; 

cp_declarator *
make_call_declarator (cp_declarator *target,
		      cp_parameter_declarator *parms,
		      cp_cv_quals cv_qualifiers,
		      tree exception_specification)
{
  cp_declarator *declarator;

  declarator = make_declarator (cdk_function);
  declarator->declarator = target;
  declarator->u.function.parameters = parms;
  declarator->u.function.qualifiers = cv_qualifiers;
  declarator->u.function.exception_specification = exception_specification;

  return declarator;
}