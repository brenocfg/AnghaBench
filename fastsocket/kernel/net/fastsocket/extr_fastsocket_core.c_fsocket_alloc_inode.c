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
struct super_block {int dummy; } ;
struct inode {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/ * file; int /*<<< orphan*/ * sk; int /*<<< orphan*/ * ops; scalar_t__ flags; int /*<<< orphan*/  state; int /*<<< orphan*/ * fasync_list; int /*<<< orphan*/  wait; } ;
struct socket_alloc {struct inode vfs_inode; TYPE_1__ socket; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUG ; 
 int /*<<< orphan*/  DPRINTK (int /*<<< orphan*/ ,char*,struct inode*) ; 
 int /*<<< orphan*/  SS_UNCONNECTED ; 
 struct socket_alloc* fsocket_alloc_socket_mem () ; 
 int /*<<< orphan*/  fsocket_free_socket_mem (struct socket_alloc*) ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 scalar_t__ security_inode_alloc (struct inode*) ; 

struct inode *fsocket_alloc_inode(struct super_block *sb)
{
	struct socket_alloc *ei;

	ei = fsocket_alloc_socket_mem();
	if (!ei)
		return NULL;

	if (security_inode_alloc(&ei->vfs_inode)) {
		fsocket_free_socket_mem(ei);
		return NULL;
	}

	init_waitqueue_head(&ei->socket.wait);

	ei->socket.fasync_list = NULL;
	ei->socket.state = SS_UNCONNECTED;
	ei->socket.flags = 0;
	ei->socket.ops = NULL;
	ei->socket.sk = NULL;
	ei->socket.file = NULL;

	DPRINTK(DEBUG, "Allocate inode 0x%p\n", &ei->vfs_inode);

	return &ei->vfs_inode;
}