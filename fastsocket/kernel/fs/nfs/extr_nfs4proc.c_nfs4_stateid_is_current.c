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
struct nfs_open_context {int dummy; } ;
struct nfs_lock_context {int dummy; } ;
typedef  int /*<<< orphan*/  nfs4_stateid ;
typedef  int /*<<< orphan*/  fmode_t ;

/* Variables and functions */
 scalar_t__ nfs4_set_rw_stateid (int /*<<< orphan*/ *,struct nfs_open_context const*,struct nfs_lock_context const*,int /*<<< orphan*/ ) ; 
 int nfs4_stateid_match (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool nfs4_stateid_is_current(nfs4_stateid *stateid,
		const struct nfs_open_context *ctx,
		const struct nfs_lock_context *l_ctx,
		fmode_t fmode)
{
	nfs4_stateid current_stateid;

	if (nfs4_set_rw_stateid(&current_stateid, ctx, l_ctx, fmode))
		return false;
	return nfs4_stateid_match(stateid, &current_stateid);
}