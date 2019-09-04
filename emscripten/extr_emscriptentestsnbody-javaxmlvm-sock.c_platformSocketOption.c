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
typedef  int I_32 ;

/* Variables and functions */
 int HYPORT_ERROR_SOCKET_OPTUNSUPP ; 
#define  HY_IP_MULTICAST_LOOP 141 
#define  HY_IP_TOS 140 
#define  HY_MCAST_ADD_MEMBERSHIP 139 
#define  HY_MCAST_DROP_MEMBERSHIP 138 
#define  HY_MCAST_INTERFACE 137 
#define  HY_MCAST_TTL 136 
#define  HY_SO_BROADCAST 135 
#define  HY_SO_KEEPALIVE 134 
#define  HY_SO_LINGER 133 
#define  HY_SO_OOBINLINE 132 
#define  HY_SO_RCVBUF 131 
#define  HY_SO_REUSEADDR 130 
#define  HY_SO_SNDBUF 129 
#define  HY_TCP_NODELAY 128 
 int OS_IP_TOS ; 
 int OS_MCAST_ADD_MEMBERSHIP ; 
 int OS_MCAST_DROP_MEMBERSHIP ; 
 int OS_MCAST_INTERFACE ; 
 int OS_MCAST_LOOP ; 
 int OS_MCAST_TTL ; 
 int OS_SO_BROADCAST ; 
 int OS_SO_KEEPALIVE ; 
 int OS_SO_LINGER ; 
 int OS_SO_OOBINLINE ; 
 int OS_SO_RCVBUF ; 
 int OS_SO_REUSEADDR ; 
 int OS_SO_SNDBUF ; 
 int OS_TCP_NODELAY ; 

I_32
platformSocketOption (I_32 portableSocketOption)
{
    switch (portableSocketOption)
    {
        case HY_SO_LINGER:
            return OS_SO_LINGER;
        case HY_SO_KEEPALIVE:
            return OS_SO_KEEPALIVE;
        case HY_TCP_NODELAY:
            return OS_TCP_NODELAY;
        case HY_MCAST_TTL:
            return OS_MCAST_TTL;
        case HY_MCAST_ADD_MEMBERSHIP:
            return OS_MCAST_ADD_MEMBERSHIP;
        case HY_MCAST_DROP_MEMBERSHIP:
            return OS_MCAST_DROP_MEMBERSHIP;
        case HY_MCAST_INTERFACE:
            return OS_MCAST_INTERFACE;
        case HY_SO_REUSEADDR:
            return OS_SO_REUSEADDR;
        case HY_SO_SNDBUF:
            return OS_SO_SNDBUF;
        case HY_SO_RCVBUF:
            return OS_SO_RCVBUF;
        case HY_SO_BROADCAST:
            return OS_SO_BROADCAST;
            
        case HY_SO_OOBINLINE:
            return OS_SO_OOBINLINE;
        case HY_IP_MULTICAST_LOOP:
            return OS_MCAST_LOOP;
        case HY_IP_TOS:
            return OS_IP_TOS;
#if defined(IPv6_FUNCTION_SUPPORT)
        case HY_MCAST_INTERFACE_2:
            return OS_MCAST_INTERFACE_2;
        case HY_IPV6_ADD_MEMBERSHIP:
            return OS_IPV6_ADD_MEMBERSHIP;
        case HY_IPV6_DROP_MEMBERSHIP:
            return OS_IPV6_DROP_MEMBERSHIP;
#endif
            
    }
    return HYPORT_ERROR_SOCKET_OPTUNSUPP;
}