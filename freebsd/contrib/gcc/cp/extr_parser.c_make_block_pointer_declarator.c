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
typedef  int /*<<< orphan*/  tree ;
struct TYPE_3__ {int /*<<< orphan*/  qualifiers; } ;
struct TYPE_4__ {TYPE_1__ block_pointer; } ;
struct cp_declarator {TYPE_2__ u; struct cp_declarator* declarator; int /*<<< orphan*/  attributes; } ;
typedef  struct cp_declarator cp_declarator ;
typedef  int /*<<< orphan*/  cp_cv_quals ;

/* Variables and functions */
 int /*<<< orphan*/  cdk_block_pointer ; 
 struct cp_declarator* make_declarator (int /*<<< orphan*/ ) ; 

cp_declarator *
make_block_pointer_declarator (tree attributes,
				cp_cv_quals quals,
				cp_declarator *target)
{
  struct cp_declarator *itarget = target;
  struct cp_declarator *ret = make_declarator (cdk_block_pointer);

  /* APPLE LOCAL radar 5847213 */
  /* code removed */


  ret->attributes = attributes;
  ret->declarator = itarget;
  ret->u.block_pointer.qualifiers = quals;
  return ret;
}