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
struct nfs_direct_req {int dummy; } ;
struct inode {int /*<<< orphan*/  i_mapping; } ;

/* Variables and functions */
 int /*<<< orphan*/  nfs_direct_complete (struct nfs_direct_req*) ; 
 int /*<<< orphan*/  nfs_zap_mapping (struct inode*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void nfs_direct_write_complete(struct nfs_direct_req *dreq, struct inode *inode)
{
	nfs_zap_mapping(inode, inode->i_mapping);
	nfs_direct_complete(dreq);
}