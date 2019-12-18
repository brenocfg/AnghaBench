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
 int /*<<< orphan*/  PARM ; 
 int /*<<< orphan*/  decl_attributes (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  grokdeclarator (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 

tree
grokparm (const struct c_parm *parm)
{
  tree decl = grokdeclarator (parm->declarator, parm->specs, PARM, false,
			      NULL);

  decl_attributes (&decl, parm->attrs, 0);

  return decl;
}