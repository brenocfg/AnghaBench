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
struct c_parm {int /*<<< orphan*/  attrs; int /*<<< orphan*/  specs; int /*<<< orphan*/  declarator; } ;

/* Variables and functions */
 int /*<<< orphan*/  NULL_TREE ; 
 int /*<<< orphan*/  PARM ; 
 int /*<<< orphan*/  decl_attributes (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  finish_decl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  grokdeclarator (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pushdecl (int /*<<< orphan*/ ) ; 

void
push_parm_decl (const struct c_parm *parm)
{
  tree decl;

  decl = grokdeclarator (parm->declarator, parm->specs, PARM, false, NULL);
  decl_attributes (&decl, parm->attrs, 0);

  decl = pushdecl (decl);

  finish_decl (decl, NULL_TREE, NULL_TREE);
}