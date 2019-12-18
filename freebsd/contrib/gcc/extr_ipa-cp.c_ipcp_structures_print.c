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
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  ipa_method_modify_print (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ipa_method_tree_print (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ipcp_callsite_param_print (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ipcp_method_cval_print (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ipcp_method_scale_print (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
ipcp_structures_print (FILE * f)
{
  ipcp_method_cval_print (f);
  ipcp_method_scale_print (f);
  ipa_method_tree_print (f);
  ipa_method_modify_print (f);
  ipcp_callsite_param_print (f);
}