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
struct nfs_inode {int /*<<< orphan*/ * layout; int /*<<< orphan*/  rwsem; scalar_t__ delegation_state; int /*<<< orphan*/ * delegation; int /*<<< orphan*/  open_states; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  init_rwsem (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void nfs4_init_once(struct nfs_inode *nfsi)
{
#ifdef CONFIG_NFS_V4
	INIT_LIST_HEAD(&nfsi->open_states);
	nfsi->delegation = NULL;
	nfsi->delegation_state = 0;
	init_rwsem(&nfsi->rwsem);
	nfsi->layout = NULL;
#endif
}