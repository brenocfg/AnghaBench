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
struct nsproxy {TYPE_1__* net_ns; } ;
struct ctl_table_set {int dummy; } ;
struct ctl_table_root {int dummy; } ;
struct TYPE_2__ {struct ctl_table_set sysctls; } ;

/* Variables and functions */

__attribute__((used)) static struct ctl_table_set *
net_ctl_header_lookup(struct ctl_table_root *root, struct nsproxy *namespaces)
{
	return &namespaces->net_ns->sysctls;
}