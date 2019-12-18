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
struct se_node_acl {int /*<<< orphan*/  acl_pr_ref_count; } ;

/* Variables and functions */
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cpu_relax () ; 

void core_tpg_wait_for_nacl_pr_ref(struct se_node_acl *nacl)
{
	while (atomic_read(&nacl->acl_pr_ref_count) != 0)
		cpu_relax();
}