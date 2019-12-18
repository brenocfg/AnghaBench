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
typedef  int /*<<< orphan*/  uint32_t ;
struct nfs_open_owner {int dummy; } ;
struct nfs_open_file {int dummy; } ;
typedef  int /*<<< orphan*/  nfsnode_t ;

/* Variables and functions */
 int nfs_open_file_find_internal (int /*<<< orphan*/ ,struct nfs_open_owner*,struct nfs_open_file**,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

int
nfs_open_file_find(
	nfsnode_t np,
	struct nfs_open_owner *noop,
	struct nfs_open_file **nofpp,
	uint32_t accessMode,
	uint32_t denyMode,
	int alloc)
{
	*nofpp = NULL;
	return nfs_open_file_find_internal(np, noop, nofpp, accessMode, denyMode, alloc);
}