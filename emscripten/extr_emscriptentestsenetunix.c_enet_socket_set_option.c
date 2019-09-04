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
typedef  int ENetSocketOption ;
typedef  int /*<<< orphan*/  ENetSocket ;

/* Variables and functions */
#define  ENET_SOCKOPT_BROADCAST 134 
#define  ENET_SOCKOPT_NONBLOCK 133 
#define  ENET_SOCKOPT_RCVBUF 132 
#define  ENET_SOCKOPT_RCVTIMEO 131 
#define  ENET_SOCKOPT_REUSEADDR 130 
#define  ENET_SOCKOPT_SNDBUF 129 
#define  ENET_SOCKOPT_SNDTIMEO 128 
 int /*<<< orphan*/  FIONBIO ; 
 int /*<<< orphan*/  SOL_SOCKET ; 
 int /*<<< orphan*/  SO_BROADCAST ; 
 int /*<<< orphan*/  SO_RCVBUF ; 
 int /*<<< orphan*/  SO_RCVTIMEO ; 
 int /*<<< orphan*/  SO_REUSEADDR ; 
 int /*<<< orphan*/  SO_SNDBUF ; 
 int /*<<< orphan*/  SO_SNDTIMEO ; 
 int ioctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int setsockopt (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int) ; 

int
enet_socket_set_option (ENetSocket socket, ENetSocketOption option, int value)
{
    int result = -1;
    switch (option)
    {
        case ENET_SOCKOPT_NONBLOCK:
#ifdef HAS_FCNTL
            result = fcntl (socket, F_SETFL, O_NONBLOCK | fcntl (socket, F_GETFL));
#else
            result = ioctl (socket, FIONBIO, & value);
#endif
            break;

        case ENET_SOCKOPT_BROADCAST:
            result = setsockopt (socket, SOL_SOCKET, SO_BROADCAST, (char *) & value, sizeof (int));
            break;

        case ENET_SOCKOPT_REUSEADDR:
            result = setsockopt (socket, SOL_SOCKET, SO_REUSEADDR, (char *) & value, sizeof (int));
            break;

        case ENET_SOCKOPT_RCVBUF:
            result = setsockopt (socket, SOL_SOCKET, SO_RCVBUF, (char *) & value, sizeof (int));
            break;

        case ENET_SOCKOPT_SNDBUF:
            result = setsockopt (socket, SOL_SOCKET, SO_SNDBUF, (char *) & value, sizeof (int));
            break;

        case ENET_SOCKOPT_RCVTIMEO:
            result = setsockopt (socket, SOL_SOCKET, SO_RCVTIMEO, (char *) & value, sizeof (int));
            break;

        case ENET_SOCKOPT_SNDTIMEO:
            result = setsockopt (socket, SOL_SOCKET, SO_SNDTIMEO, (char *) & value, sizeof (int));
            break;

        default:
            break;
    }
    return result == -1 ? -1 : 0;
}