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
typedef  int u32 ;
typedef  int /*<<< orphan*/  u16_t ;
typedef  int /*<<< orphan*/  u16 ;
struct netsocket {int flags; TYPE_1__* conn; } ;
typedef  int /*<<< orphan*/  s32 ;
struct TYPE_2__ {int /*<<< orphan*/  recvavail; } ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  ENOTSOCK ; 
#define  FIONBIO 129 
#define  FIONREAD 128 
 int /*<<< orphan*/  LWIP_DEBUGF (int /*<<< orphan*/ ,char*) ; 
 int O_NONBLOCK ; 
 int /*<<< orphan*/  SOCKETS_DEBUG ; 
 struct netsocket* get_socket (int /*<<< orphan*/ ) ; 

s32 net_ioctl(s32 s, u32 cmd, void *argp)
{
	struct netsocket *sock = get_socket(s);

	if(!sock) return -ENOTSOCK;

	switch (cmd) {
		case FIONREAD:
			if(!argp) return -EINVAL;

			*((u16_t*)argp) = sock->conn->recvavail;

			LWIP_DEBUGF(SOCKETS_DEBUG, ("net_ioctl(%d, FIONREAD, %p) = %u\n", s, argp, *((u16*)argp)));
			return 0;

		case FIONBIO:
			if(argp && *(u32*)argp)
				sock->flags |= O_NONBLOCK;
			else
				sock->flags &= ~O_NONBLOCK;
			LWIP_DEBUGF(SOCKETS_DEBUG, ("net_ioctl(%d, FIONBIO, %d)\n", s, !!(sock->flags&O_NONBLOCK)));
			return 0;

		default:
			LWIP_DEBUGF(SOCKETS_DEBUG, ("net_ioctl(%d, UNIMPL: 0x%lx, %p)\n", s, cmd, argp));
			return -EINVAL;
	}
}