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
struct TYPE_4__ {int /*<<< orphan*/  s_addr; } ;
struct sockaddr_in {int msg_namelen; size_t msg_iovlen; struct iovec* msg_iov; struct sockaddr_in* msg_name; TYPE_1__ sin_addr; int /*<<< orphan*/  sin_port; int /*<<< orphan*/  sin_family; } ;
struct msghdr {int msg_namelen; size_t msg_iovlen; struct iovec* msg_iov; struct msghdr* msg_name; TYPE_1__ sin_addr; int /*<<< orphan*/  sin_port; int /*<<< orphan*/  sin_family; } ;
struct iovec {int dummy; } ;
struct TYPE_5__ {int /*<<< orphan*/  host; int /*<<< orphan*/  port; } ;
typedef  int /*<<< orphan*/  ENetSocket ;
typedef  int /*<<< orphan*/  ENetBuffer ;
typedef  TYPE_2__ ENetAddress ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET ; 
 int /*<<< orphan*/  ENET_HOST_TO_NET_16 (int /*<<< orphan*/ ) ; 
 scalar_t__ EWOULDBLOCK ; 
 int /*<<< orphan*/  MSG_NOSIGNAL ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  memset (struct sockaddr_in*,int /*<<< orphan*/ ,int) ; 
 int sendmsg (int /*<<< orphan*/ ,struct sockaddr_in*,int /*<<< orphan*/ ) ; 

int
enet_socket_send (ENetSocket socket,
                  const ENetAddress * address,
                  const ENetBuffer * buffers,
                  size_t bufferCount)
{
    struct msghdr msgHdr;
    struct sockaddr_in sin;
    int sentLength;

    memset (& msgHdr, 0, sizeof (struct msghdr));

    if (address != NULL)
    {
        memset (& sin, 0, sizeof (struct sockaddr_in));

        sin.sin_family = AF_INET;
        sin.sin_port = ENET_HOST_TO_NET_16 (address -> port);
        sin.sin_addr.s_addr = address -> host;

        msgHdr.msg_name = & sin;
        msgHdr.msg_namelen = sizeof (struct sockaddr_in);
    }

    msgHdr.msg_iov = (struct iovec *) buffers;
    msgHdr.msg_iovlen = bufferCount;

    sentLength = sendmsg (socket, & msgHdr, MSG_NOSIGNAL);
    
    if (sentLength == -1)
    {
       if (errno == EWOULDBLOCK)
         return 0;

       return -1;
    }

    return sentLength;
}