#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ tree ;
struct TYPE_5__ {scalar_t__ qualifying_scope; } ;
struct TYPE_6__ {TYPE_1__ id; } ;
struct TYPE_7__ {scalar_t__ kind; TYPE_2__ u; struct TYPE_7__* declarator; } ;
typedef  TYPE_3__ cp_declarator ;

/* Variables and functions */
 scalar_t__ NULL_TREE ; 
 scalar_t__ cdk_id ; 

tree
get_scope_of_declarator (const cp_declarator *declarator)
{
  while (declarator && declarator->kind != cdk_id)
    declarator = declarator->declarator;

  /* If the declarator-id is a SCOPE_REF, the scope in which the
     declaration occurs is the first operand.  */
  if (declarator
      && declarator->u.id.qualifying_scope)
    return declarator->u.id.qualifying_scope;

  /* Otherwise, the declarator is not a qualified name; the entity will
     be declared in the current scope.  */
  return NULL_TREE;
}