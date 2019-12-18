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
struct socket_alloc {int dummy; } ;
struct inode {int /*<<< orphan*/  i_mode; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUG ; 
 int /*<<< orphan*/  DPRINTK (int /*<<< orphan*/ ,char*,struct inode*) ; 
 scalar_t__ SOCKET_I (struct inode*) ; 
 scalar_t__ S_ISSOCK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fsock_release_sock (scalar_t__) ; 
 int /*<<< orphan*/  fsocket_free_socket_mem (struct socket_alloc*) ; 
 int /*<<< orphan*/  security_inode_free (struct inode*) ; 

void fsocket_destroy_inode(struct inode *inode)
{
	DPRINTK(DEBUG, "Free inode 0x%p\n", inode);

	if (S_ISSOCK(inode->i_mode)) {
		security_inode_free(inode);
	}
	fsock_release_sock(SOCKET_I(inode));
	fsocket_free_socket_mem((struct socket_alloc*)(SOCKET_I(inode)));
}