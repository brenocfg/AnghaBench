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
typedef  int /*<<< orphan*/ * ipa_reference_local_vars_info_t ;

/* Variables and functions */
 int /*<<< orphan*/  check_tree (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  look_for_address_of (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
check_rhs_var (ipa_reference_local_vars_info_t local, tree t)
{
  look_for_address_of (t);

  if (local == NULL) 
    return;

  check_tree(local, t, false);
}