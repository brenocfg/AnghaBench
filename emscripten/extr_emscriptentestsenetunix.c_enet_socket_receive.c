#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ s_addr; } ;
struct sockaddr_in {int /*<<< orphan*/  sin_port; TYPE_1__ sin_addr; } ;
struct msghdr {int msg_namelen; size_t msg_iovlen; struct iovec* msg_iov; struct sockaddr_in* msg_name; } ;
struct iovec {int dummy; } ;
typedef  scalar_t__ enet_uint32 ;
struct TYPE_5__ {int /*<<< orphan*/  port; scalar_t__ host; } ;
typedef  int /*<<< orphan*/  ENetSocket ;
typedef  int /*<<< orphan*/  ENetBuffer ;
typedef  TYPE_2__ ENetAddress ;

/* Variables and functions */
 int /*<<< orphan*/  ENET_NET_TO_HOST_16 (int /*<<< orphan*/ ) ; 
 scalar_t__ EWOULDBLOCK ; 
 int /*<<< orphan*/  MSG_NOSIGNAL ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  memset (struct msghdr*,int /*<<< orphan*/ ,int) ; 
 int recvmsg (int /*<<< orphan*/ ,struct msghdr*,int /*<<< orphan*/ ) ; 

int
enet_socket_receive (ENetSocket socket,
                     ENetAddress * address,
                     ENetBuffer * buffers,
                     size_t bufferCount)
{
    struct msghdr msgHdr;
    struct sockaddr_in sin;
    int recvLength;

    memset (& msgHdr, 0, sizeof (struct msghdr));

    if (address != NULL)
    {
        msgHdr.msg_name = & sin;
        msgHdr.msg_namelen = sizeof (struct sockaddr_in);
    }

    msgHdr.msg_iov = (struct iovec *) buffers;
    msgHdr.msg_iovlen = bufferCount;

    recvLength = recvmsg (socket, & msgHdr, MSG_NOSIGNAL);

    if (recvLength == -1)
    {
       if (errno == EWOULDBLOCK)
         return 0;

       return -1;
    }

#ifdef HAS_MSGHDR_FLAGS
    if (msgHdr.msg_flags & MSG_TRUNC)
      return -1;
#endif

    if (address != NULL)
    {
        address -> host = (enet_uint32) sin.sin_addr.s_addr;
        address -> port = ENET_NET_TO_HOST_16 (sin.sin_port);
    }

    return recvLength;
}