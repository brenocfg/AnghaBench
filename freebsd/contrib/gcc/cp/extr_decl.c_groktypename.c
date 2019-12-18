#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ tree ;
typedef  int /*<<< orphan*/  cp_declarator ;
struct TYPE_4__ {scalar_t__ attributes; } ;
typedef  TYPE_1__ cp_decl_specifier_seq ;

/* Variables and functions */
 scalar_t__ NULL_TREE ; 
 int /*<<< orphan*/  TYPENAME ; 
 int /*<<< orphan*/  cplus_decl_attributes (scalar_t__*,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ grokdeclarator (int /*<<< orphan*/  const*,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*) ; 

tree
groktypename (cp_decl_specifier_seq *type_specifiers,
	      const cp_declarator *declarator)
{
  tree attrs;
  tree type;
  attrs = type_specifiers->attributes;
  type_specifiers->attributes = NULL_TREE;
  type = grokdeclarator (declarator, type_specifiers, TYPENAME, 0, &attrs);
  if (attrs)
    cplus_decl_attributes (&type, attrs, 0);
  return type;
}