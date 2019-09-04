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
struct sockaddr_in {TYPE_1__ sin_addr; int /*<<< orphan*/  sin_port; int /*<<< orphan*/  sin_family; } ;
struct sockaddr {int dummy; } ;
struct TYPE_5__ {int /*<<< orphan*/  host; int /*<<< orphan*/  port; } ;
typedef  int /*<<< orphan*/  ENetSocket ;
typedef  TYPE_2__ ENetAddress ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET ; 
 int /*<<< orphan*/  ENET_HOST_TO_NET_16 (int /*<<< orphan*/ ) ; 
 int connect (int /*<<< orphan*/ ,struct sockaddr*,int) ; 
 int /*<<< orphan*/  memset (struct sockaddr_in*,int /*<<< orphan*/ ,int) ; 

int
enet_socket_connect (ENetSocket socket, const ENetAddress * address)
{
    struct sockaddr_in sin;

    memset (& sin, 0, sizeof (struct sockaddr_in));

    sin.sin_family = AF_INET;
    sin.sin_port = ENET_HOST_TO_NET_16 (address -> port);
    sin.sin_addr.s_addr = address -> host;

    return connect (socket, (struct sockaddr *) & sin, sizeof (struct sockaddr_in));
}