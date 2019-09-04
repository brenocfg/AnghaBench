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
 int HYPORT_ERROR_SOCKET_SOCKLEVELINVALID ; 
#define  HY_IPPROTO_IP 130 
#define  HY_IPPROTO_TCP 129 
#define  HY_SOL_SOCKET 128 
 int OS_IPPROTO_IP ; 
 int OS_IPPROTO_TCP ; 
 int OS_SOL_SOCKET ; 

I_32
platformSocketLevel (I_32 portableSocketLevel)
{
    switch (portableSocketLevel)
    {
        case HY_SOL_SOCKET:
            return OS_SOL_SOCKET;
        case HY_IPPROTO_TCP:
            return OS_IPPROTO_TCP;
        case HY_IPPROTO_IP:
            return OS_IPPROTO_IP;
#if defined(IPv6_FUNCTION_SUPPORT)
        case HY_IPPROTO_IPV6:
            return OS_IPPROTO_IPV6;
#endif
            
    }
    return HYPORT_ERROR_SOCKET_SOCKLEVELINVALID;
}