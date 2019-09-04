#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct hysocket_struct {int dummy; } ;
typedef  TYPE_1__* hysocket_t ;
struct TYPE_5__ {int sock; scalar_t__ family; } ;
typedef  scalar_t__ I_32 ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET ; 
 scalar_t__ FD_CLOEXEC ; 
 int /*<<< orphan*/  F_GETFD ; 
 int /*<<< orphan*/  F_SETFD ; 
 scalar_t__ HYADDR_FAMILY_AFINET4 ; 
 scalar_t__ HYADDR_FAMILY_AFINET6 ; 
 scalar_t__ HYADDR_FAMILY_UNSPEC ; 
 scalar_t__ HYPORT_ERROR_SOCKET_BADAF ; 
 scalar_t__ HYPORT_ERROR_SOCKET_BADPROTO ; 
 scalar_t__ HYPORT_ERROR_SOCKET_BADTYPE ; 
 scalar_t__ HYSOCK_DEFPROTOCOL ; 
 scalar_t__ HYSOCK_DGRAM ; 
 scalar_t__ HYSOCK_STREAM ; 
 TYPE_1__* INVALID_SOCKET ; 
 int /*<<< orphan*/  SOCK_DGRAM ; 
 int /*<<< orphan*/  SOCK_STREAM ; 
 TYPE_1__* XMLVM_ATOMIC_MALLOC (int) ; 
 scalar_t__ errno ; 
 scalar_t__ fcntl (int,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  findError (scalar_t__) ; 
 scalar_t__ hyerror_set_last_error (scalar_t__,int /*<<< orphan*/ ) ; 
 int socket (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

I_32 hysock_socket (hysocket_t * handle, I_32 family, I_32 socktype, I_32 protocol)
{
    I_32 rc = 0;
    int sock;
    
    /* initialize return hysocket_t to invalid socket */
    *handle = INVALID_SOCKET;
    
    if (protocol != HYSOCK_DEFPROTOCOL)
    {
        rc = HYPORT_ERROR_SOCKET_BADPROTO;
    }
    else if ((socktype != HYSOCK_STREAM) && (socktype != HYSOCK_DGRAM))
    {
        rc = HYPORT_ERROR_SOCKET_BADTYPE;
    }
    else if (family != HYADDR_FAMILY_AFINET6 && family != HYADDR_FAMILY_AFINET4
             && family != HYADDR_FAMILY_UNSPEC)
    {
        rc = HYPORT_ERROR_SOCKET_BADAF;
    }
    
    if (rc == 0)
    {
        
#if defined(IPv6_FUNCTION_SUPPORT)
        if (family != HYADDR_FAMILY_AFINET4)
        {
            family = HYADDR_FAMILY_AFINET6;
            sock =
            socket (AF_INET6,
                    ((socktype == HYSOCK_STREAM) ? SOCK_STREAM : SOCK_DGRAM),
                    0);
            if (sock < 0)
            {
                rc = errno;
                HYSOCKDEBUG ("<socket failed, err=%d>\n", rc);
                return portLibrary->error_set_last_error (portLibrary, rc,
                                                          findError (rc));
            }
        }
        else
        {
#endif
            
            sock =
            socket (AF_INET,
                    ((socktype == HYSOCK_STREAM) ? SOCK_STREAM : SOCK_DGRAM),
                    0);
            
            if (sock < 0)
            {
                rc = errno;
                return hyerror_set_last_error(rc, findError(rc));
            }
            
#if defined(IPv6_FUNCTION_SUPPORT)
        }
#endif
        
    }
    
    if (rc == 0)
    {
        /*Tag this descriptor as being non-inheritable */
        I_32 fdflags = fcntl (sock, F_GETFD, 0);
        fcntl (sock, F_SETFD, fdflags | FD_CLOEXEC);
        
        /* set up the socket structure */
        *handle = XMLVM_ATOMIC_MALLOC(sizeof (struct hysocket_struct));
        
#if (defined(VALIDATE_ALLOCATIONS))
        if (*handle == NULL)
        {
            close (sock);
            *handle = INVALID_SOCKET;
            return HYPORT_ERROR_SOCKET_NOBUFFERS;
        }
#endif
        
        (*handle)->sock = sock;
        (*handle)->family = family;
    }
    return rc;
}