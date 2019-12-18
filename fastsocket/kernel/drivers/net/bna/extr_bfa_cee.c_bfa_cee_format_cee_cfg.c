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
struct bfa_cee_attr {int /*<<< orphan*/  lldp_remote; } ;

/* Variables and functions */
 int /*<<< orphan*/  bfa_cee_format_lldp_cfg (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
bfa_cee_format_cee_cfg(void *buffer)
{
	struct bfa_cee_attr *cee_cfg = buffer;
	bfa_cee_format_lldp_cfg(&cee_cfg->lldp_remote);
}