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
struct socket_alloc {int dummy; } ;
struct socket {scalar_t__ type; int /*<<< orphan*/ * file; int /*<<< orphan*/ * sk; int /*<<< orphan*/ * ops; scalar_t__ flags; int /*<<< orphan*/  state; int /*<<< orphan*/ * fasync_list; int /*<<< orphan*/  wait; } ;
struct inode_operations {int dummy; } ;
struct inode {unsigned int i_ino; int i_mode; int /*<<< orphan*/  i_gid; int /*<<< orphan*/  i_uid; scalar_t__ i_state; int /*<<< orphan*/  i_sb_list; int /*<<< orphan*/  i_list; int /*<<< orphan*/  i_count; int /*<<< orphan*/  i_sb; struct file_operations const* i_fop; struct inode_operations const* i_op; } ;
struct file_operations {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  mnt_sb; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUG ; 
 int /*<<< orphan*/  DPRINTK (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  ERR ; 
 unsigned int FSOCKET_INODE_START ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 struct inode* SOCK_INODE (struct socket*) ; 
 int /*<<< orphan*/  SS_UNCONNECTED ; 
 int S_IFSOCK ; 
 int S_IRWXUGO ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 int /*<<< orphan*/  __module_get (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  current_fsgid () ; 
 int /*<<< orphan*/  current_fsuid () ; 
 TYPE_1__* fastsocket_mnt ; 
 scalar_t__ fsocket_alloc_socket_mem () ; 
 int /*<<< orphan*/  fsocket_free_socket_mem (struct socket_alloc*) ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kmemcheck_annotate_bitfield (struct socket*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  module_put (int /*<<< orphan*/ ) ; 
 scalar_t__ security_inode_alloc (struct inode*) ; 
 int /*<<< orphan*/  type ; 

__attribute__((used)) static struct socket *fsocket_alloc_socket(void)
{
#define FSOCKET_INODE_START	( 1 << 12 )

	static const struct inode_operations empty_iops;
	static const struct file_operations empty_fops;
	struct socket *sock;
	//FIXME: Just guess this inode number is not something really matters.
	static unsigned int last_ino = FSOCKET_INODE_START;
	struct inode *inode = NULL;	

	sock = (struct socket *)fsocket_alloc_socket_mem();
	if (!sock) {
		DPRINTK(ERR, "Fail to allocate sock\n");
		goto err1;
	}
	
	__module_get(THIS_MODULE);
	
	if (security_inode_alloc(SOCK_INODE(sock))) {
		goto err2;
	}
	
	init_waitqueue_head(&sock->wait);
	
	sock->fasync_list = NULL;
	sock->state = SS_UNCONNECTED;
	sock->flags = 0;
	sock->ops = NULL;
	sock->sk = NULL;
	sock->file = NULL;
	
	sock->type = 0;
	
	inode = SOCK_INODE(sock);
	
	inode->i_op = &empty_iops;
	inode->i_fop = &empty_fops;
	inode->i_sb = fastsocket_mnt->mnt_sb;
	atomic_set(&inode->i_count, 1);
	
	INIT_LIST_HEAD(&inode->i_list);
	INIT_LIST_HEAD(&inode->i_sb_list);
	
	inode->i_ino = ++last_ino;
	inode->i_state = 0;
	
	kmemcheck_annotate_bitfield(sock, type);
	inode->i_mode = S_IFSOCK | S_IRWXUGO;
	inode->i_uid = current_fsuid();
	inode->i_gid = current_fsgid();

	
	
	DPRINTK(DEBUG, "Allocat inode 0x%p\n", inode);

	return sock;
	
err2:
	module_put(THIS_MODULE);
	fsocket_free_socket_mem((struct socket_alloc*)sock);
err1:
	return NULL;
}