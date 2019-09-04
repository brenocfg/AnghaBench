#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct hysockaddr_struct {int dummy; } ;
typedef  int /*<<< orphan*/  hysocket_t ;
typedef  TYPE_2__* hysockaddr_t ;
typedef  int /*<<< orphan*/  U_8 ;
typedef  int /*<<< orphan*/  U_32 ;
typedef  void* U_16 ;
struct TYPE_6__ {int /*<<< orphan*/  s_addr; } ;
struct TYPE_8__ {int /*<<< orphan*/  sin_family; void* sin_port; TYPE_1__ sin_addr; } ;
struct TYPE_7__ {int /*<<< orphan*/  addr; } ;
typedef  TYPE_3__ OSSOCKADDR ;
typedef  int /*<<< orphan*/  I_32 ;
typedef  scalar_t__ I_16 ;

/* Variables and functions */
 scalar_t__ HYADDR_FAMILY_AFINET4 ; 
 int /*<<< orphan*/  HYSOCK_INADDR_LEN ; 
 int /*<<< orphan*/  OS_AF_INET4 ; 
 int /*<<< orphan*/  XMLVM_BZERO (TYPE_2__*,int) ; 
 int /*<<< orphan*/  XMLVM_MEMCPY (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  map_addr_family_Hy_to_OS (scalar_t__) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

I_32 hysock_sockaddr_init6 (hysockaddr_t handle, U_8 * addr, I_32 addrlength,
                            I_16 family, U_16 nPort, U_32 flowinfo, U_32 scope_id,
                            hysocket_t sock)
{
    OSSOCKADDR *sockaddr;
#if defined(IPv6_FUNCTION_SUPPORT)
    OSSOCKADDR_IN6 *sockaddr_6;
#endif
    
    XMLVM_BZERO(handle, sizeof (struct hysockaddr_struct));
    
    if (family == HYADDR_FAMILY_AFINET4)
    {
#if defined(IPv6_FUNCTION_SUPPORT)
        if (hysock_socketIsValid (portLibrary, sock) &&
            (((struct hysocket_struct *) sock)->family ==
             HYADDR_FAMILY_AFINET6))
        {
            /* to talk IPv4 on an IPv6 socket we need to map the IPv4 address to an IPv6 format.  If mapAddress is true then we do this */
            sockaddr_6 = (OSSOCKADDR_IN6 *) & handle->addr;
            memset (sockaddr_6->sin6_addr.s6_addr, 0, 16);
            memcpy (&(sockaddr_6->sin6_addr.s6_addr[12]), addr, addrlength);
            /* do a check if it is the any address.  we know the top 4 bytes of sockaddr_6->sin6_addr.s6_addr are 0's as we just cleared the,
             so we use them to do the check */
            if (memcmp (sockaddr_6->sin6_addr.s6_addr, addr, addrlength) != 0)
            {
                /* if it is the any address then use the IPv6 any address */
                sockaddr_6->sin6_addr.s6_addr[10] = 0xFF;
                sockaddr_6->sin6_addr.s6_addr[11] = 0xFF;
            }
            sockaddr_6->sin6_port = nPort;
            sockaddr_6->sin6_family = OS_AF_INET6;
            sockaddr_6->sin6_scope_id = scope_id;
            sockaddr_6->sin6_flowinfo = htonl (flowinfo);
#if defined(FREEBSD)
            sockaddr_6->sin6_len = sizeof(OSSOCKADDR_IN6);
#endif
        }
        else
        {
#endif
            
            /* just initialize the IPv4 address as is as it will be used with an IPv4 Socket */
            sockaddr = (OSSOCKADDR *) & handle->addr;
            XMLVM_MEMCPY (&sockaddr->sin_addr.s_addr, addr, addrlength);
            sockaddr->sin_port = nPort;
            sockaddr->sin_family = OS_AF_INET4;
#if defined(FREEBSD)
            sockaddr->sin_len = sizeof(OSSOCKADDR);
#endif
            
#if defined(IPv6_FUNCTION_SUPPORT)
        }
#endif
        
    }
#if defined(IPv6_FUNCTION_SUPPORT)
    else if (family == HYADDR_FAMILY_AFINET6)
    {
        sockaddr_6 = (OSSOCKADDR_IN6 *) & handle->addr;
        memcpy (&sockaddr_6->sin6_addr.s6_addr, addr, addrlength);
        sockaddr_6->sin6_port = nPort;
        sockaddr_6->sin6_family = OS_AF_INET6;
        sockaddr_6->sin6_scope_id = scope_id;
        sockaddr_6->sin6_flowinfo = htonl (flowinfo);
#if defined(SIN6_LEN)
        sockaddr_6->sin6_len = sizeof(OSSOCKADDR_IN6);
#endif
    }
#endif
    
    else
    {
        sockaddr = (OSSOCKADDR *) & handle->addr;
        memcpy (&sockaddr->sin_addr.s_addr, addr, HYSOCK_INADDR_LEN);
        sockaddr->sin_port = nPort;
        sockaddr->sin_family = map_addr_family_Hy_to_OS (family);
#if defined(FREEBSD)
        sockaddr->sin_len = sizeof(OSSOCKADDR);
#endif
    }
    
    return 0;
}