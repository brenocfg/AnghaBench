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
struct named_label_use_entry {int /*<<< orphan*/  o_goto_locus; int /*<<< orphan*/  in_omp_scope; int /*<<< orphan*/  names_in_scope; int /*<<< orphan*/  binding_level; } ;

/* Variables and functions */
 int /*<<< orphan*/  check_previous_goto_1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
check_previous_goto (tree decl, struct named_label_use_entry *use)
{
  check_previous_goto_1 (decl, use->binding_level,
			 use->names_in_scope, use->in_omp_scope,
			 &use->o_goto_locus);
}