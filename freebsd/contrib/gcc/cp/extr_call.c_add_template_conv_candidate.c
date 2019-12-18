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
struct z_candidate {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEDUCE_CONV ; 
 int /*<<< orphan*/  NULL_TREE ; 
 struct z_candidate* add_template_candidate_real (struct z_candidate**,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct z_candidate *
add_template_conv_candidate (struct z_candidate **candidates, tree tmpl,
			     tree obj, tree arglist, tree return_type,
			     tree access_path, tree conversion_path)
{
  return
    add_template_candidate_real (candidates, tmpl, NULL_TREE, NULL_TREE,
				 arglist, return_type, access_path,
				 conversion_path, 0, obj, DEDUCE_CONV);
}