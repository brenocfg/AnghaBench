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
typedef  int /*<<< orphan*/  unification_kind_t ;
typedef  int /*<<< orphan*/  tree ;
struct z_candidate {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  NULL_TREE ; 
 struct z_candidate* add_template_candidate_real (struct z_candidate**,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct z_candidate *
add_template_candidate (struct z_candidate **candidates, tree tmpl, tree ctype,
			tree explicit_targs, tree arglist, tree return_type,
			tree access_path, tree conversion_path, int flags,
			unification_kind_t strict)
{
  return
    add_template_candidate_real (candidates, tmpl, ctype,
				 explicit_targs, arglist, return_type,
				 access_path, conversion_path,
				 flags, NULL_TREE, strict);
}