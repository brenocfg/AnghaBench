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
struct ip_fw_in_args {int /*<<< orphan*/  fwai_divert_rule; int /*<<< orphan*/  fwai_pf_rule; int /*<<< orphan*/  fwai_ipfw_rule; int /*<<< orphan*/  fwai_next_hop; } ;
struct ip_fw_args {int /*<<< orphan*/  fwa_divert_rule; int /*<<< orphan*/  fwa_pf_rule; int /*<<< orphan*/  fwa_ipfw_rule; int /*<<< orphan*/  fwa_next_hop; } ;

/* Variables and functions */

__attribute__((used)) static void
ip_input_cpin_args(struct ip_fw_args *args1, struct ip_fw_in_args *args)
{
	args->fwai_next_hop = args1->fwa_next_hop;
	args->fwai_ipfw_rule = args1->fwa_ipfw_rule;
	args->fwai_pf_rule = args1->fwa_pf_rule;
	args->fwai_divert_rule = args1->fwa_divert_rule;
}