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
struct nsproxy {int dummy; } ;
struct ctl_table_root {int dummy; } ;
struct ctl_table {int mode; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAP_NET_ADMIN ; 
 scalar_t__ capable (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int net_ctl_permissions(struct ctl_table_root *root,
			       struct nsproxy *nsproxy,
			       struct ctl_table *table)
{
	/* Allow network administrator to have same access as root. */
	if (capable(CAP_NET_ADMIN)) {
		int mode = (table->mode >> 6) & 7;
		return (mode << 6) | (mode << 3) | mode;
	}
	return table->mode;
}