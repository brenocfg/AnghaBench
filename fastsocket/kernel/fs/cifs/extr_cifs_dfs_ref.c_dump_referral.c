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
struct dfs_info3_param {int /*<<< orphan*/  path_consumed; int /*<<< orphan*/  ref_flag; int /*<<< orphan*/  server_type; int /*<<< orphan*/  flags; int /*<<< orphan*/  node_name; int /*<<< orphan*/  path_name; } ;

/* Variables and functions */
 int /*<<< orphan*/  cFYI (int,char*,int /*<<< orphan*/ ,...) ; 

__attribute__((used)) static void dump_referral(const struct dfs_info3_param *ref)
{
	cFYI(1, "DFS: ref path: %s", ref->path_name);
	cFYI(1, "DFS: node path: %s", ref->node_name);
	cFYI(1, "DFS: fl: %hd, srv_type: %hd", ref->flags, ref->server_type);
	cFYI(1, "DFS: ref_flags: %hd, path_consumed: %hd", ref->ref_flag,
				ref->path_consumed);
}