#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct net {int /*<<< orphan*/  sysctls; } ;
struct TYPE_2__ {int /*<<< orphan*/  default_set; } ;

/* Variables and functions */
 int /*<<< orphan*/  is_seen ; 
 TYPE_1__ net_sysctl_ro_root ; 
 int /*<<< orphan*/  setup_sysctl_set (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int sysctl_net_init(struct net *net)
{
	setup_sysctl_set(&net->sysctls,
			 &net_sysctl_ro_root.default_set,
			 is_seen);
	return 0;
}