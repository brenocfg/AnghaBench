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
struct sockaddr {int dummy; } ;
typedef  int socklen_t ;
typedef  scalar_t__ enet_uint32 ;
struct TYPE_5__ {int /*<<< orphan*/  port; scalar_t__ host; } ;
typedef  int ENetSocket ;
typedef  TYPE_2__ ENetAddress ;

/* Variables and functions */
 int /*<<< orphan*/  ENET_NET_TO_HOST_16 (int /*<<< orphan*/ ) ; 
 int ENET_SOCKET_NULL ; 
 int accept (int,struct sockaddr*,int*) ; 

ENetSocket
enet_socket_accept (ENetSocket socket, ENetAddress * address)
{
    int result;
    struct sockaddr_in sin;
    socklen_t sinLength = sizeof (struct sockaddr_in);

    result = accept (socket, 
                     address != NULL ? (struct sockaddr *) & sin : NULL, 
                     address != NULL ? & sinLength : NULL);
    
    if (result == -1)
      return ENET_SOCKET_NULL;

    if (address != NULL)
    {
        address -> host = (enet_uint32) sin.sin_addr.s_addr;
        address -> port = ENET_NET_TO_HOST_16 (sin.sin_port);
    }

    return result;
}