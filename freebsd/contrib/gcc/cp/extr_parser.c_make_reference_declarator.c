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
struct TYPE_7__ {int /*<<< orphan*/  class_type; int /*<<< orphan*/  qualifiers; } ;
struct TYPE_8__ {TYPE_1__ pointer; } ;
struct TYPE_9__ {TYPE_2__ u; struct TYPE_9__* declarator; } ;
typedef  TYPE_3__ cp_declarator ;
typedef  int /*<<< orphan*/  cp_cv_quals ;

/* Variables and functions */
 int /*<<< orphan*/  NULL_TREE ; 
 int /*<<< orphan*/  cdk_reference ; 
 TYPE_3__* make_declarator (int /*<<< orphan*/ ) ; 

cp_declarator *
make_reference_declarator (cp_cv_quals cv_qualifiers, cp_declarator *target)
{
  cp_declarator *declarator;

  declarator = make_declarator (cdk_reference);
  declarator->declarator = target;
  declarator->u.pointer.qualifiers = cv_qualifiers;
  declarator->u.pointer.class_type = NULL_TREE;

  return declarator;
}