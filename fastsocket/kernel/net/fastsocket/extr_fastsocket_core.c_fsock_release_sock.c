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
struct socket {TYPE_1__* ops; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* release ) (struct socket*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUG ; 
 int /*<<< orphan*/  DPRINTK (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SOCK_INODE (struct socket*) ; 
 int /*<<< orphan*/  stub1 (struct socket*) ; 

__attribute__((used)) static inline void fsock_release_sock(struct socket *sock)
{
	if (sock->ops) {
		DPRINTK(DEBUG, "Release inode socket 0x%p\n", SOCK_INODE(sock));
		sock->ops->release(sock);
		sock->ops = NULL;
	}
}