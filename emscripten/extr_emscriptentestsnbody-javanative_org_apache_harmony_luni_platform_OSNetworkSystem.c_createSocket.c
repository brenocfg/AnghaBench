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
typedef  int /*<<< orphan*/  hysocket_t ;
typedef  int /*<<< orphan*/  JAVA_OBJECT ;
typedef  scalar_t__ I_32 ;
typedef  int /*<<< orphan*/  BOOLEAN ;

/* Variables and functions */
 int HYADDR_FAMILY_AFINET4 ; 
 int HYADDR_FAMILY_UNSPEC ; 
 int /*<<< orphan*/  HYSOCK_DEFPROTOCOL ; 
 scalar_t__ hysock_socket (int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  setJavaIoFileDescriptorContents (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  throwJavaNetSocketException (scalar_t__) ; 

void createSocket (JAVA_OBJECT thisObjFD, int sockType, BOOLEAN preferIPv4Stack)
{
    I_32 result;
    hysocket_t sockdesc;
    int family = HYADDR_FAMILY_AFINET4;
    int supportsIPv6 = 0; //HARMONY_CACHE_GET (env, harmony_supports_ipv6);
    
    if (supportsIPv6 && !(preferIPv4Stack))
    {
        /* We are creating a server socket on the any address */
        family = HYADDR_FAMILY_UNSPEC;
    }
    
    result = hysock_socket (&sockdesc, family, sockType, HYSOCK_DEFPROTOCOL);
    if (0 != result)
    {
        /* ok now if we tried to create an IPv6 socket and it failed it could be that the
         platform does not have IPv6 enabled.  In this case we should revert back to 
         creating an IPv4 socket */
        if (HYADDR_FAMILY_UNSPEC == family)
        {
            /* now try to create an IPv4 socket */
            family = HYADDR_FAMILY_AFINET4;
            result = hysock_socket (&sockdesc, family, sockType, HYSOCK_DEFPROTOCOL);
        }
        
        if (0 != result)
        {
            throwJavaNetSocketException (result);
        }
    }
    
    if (0 == result)
    {
        setJavaIoFileDescriptorContents (thisObjFD, sockdesc);
    }
}