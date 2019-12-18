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
struct ctl_table_header {int dummy; } ;
struct ctl_table {int dummy; } ;
struct ctl_path {int dummy; } ;

/* Variables and functions */
 struct ctl_table_header* __register_sysctl_paths (int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct ctl_path const*,struct ctl_table*) ; 
 int /*<<< orphan*/  init_nsproxy ; 
 int /*<<< orphan*/  net_sysctl_ro_root ; 

struct ctl_table_header *register_net_sysctl_rotable(const
		struct ctl_path *path, struct ctl_table *table)
{
	return __register_sysctl_paths(&net_sysctl_ro_root,
			&init_nsproxy, path, table);
}