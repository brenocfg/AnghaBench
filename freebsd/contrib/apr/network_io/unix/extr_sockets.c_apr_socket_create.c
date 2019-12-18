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
typedef  int /*<<< orphan*/  apr_status_t ;
struct TYPE_5__ {int socketdes; int timeout; int /*<<< orphan*/  pool; scalar_t__ inherit; } ;
typedef  TYPE_1__ apr_socket_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int APR_INET ; 
 int APR_INET6 ; 
#define  APR_PROTO_SCTP 130 
#define  APR_PROTO_TCP 129 
#define  APR_PROTO_UDP 128 
 int /*<<< orphan*/  APR_SUCCESS ; 
 int APR_UNSPEC ; 
 int /*<<< orphan*/  EPROTONOSUPPORT ; 
 int FD_CLOEXEC ; 
 int /*<<< orphan*/  F_GETFD ; 
 int /*<<< orphan*/  F_SETFD ; 
 int IPPROTO_TCP ; 
 int IPPROTO_UDP ; 
 int SOCK_CLOEXEC ; 
 int /*<<< orphan*/  alloc_socket (TYPE_1__**,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  apr_pool_cleanup_register (int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  errno ; 
 int fcntl (int,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  set_socket_vars (TYPE_1__*,int,int,int) ; 
 void* socket (int,int,int) ; 
 int /*<<< orphan*/  socket_cleanup ; 

apr_status_t apr_socket_create(apr_socket_t **new, int ofamily, int type,
                               int protocol, apr_pool_t *cont)
{
    int family = ofamily, flags = 0;

#ifdef HAVE_SOCK_CLOEXEC
    flags |= SOCK_CLOEXEC;
#endif

    if (family == APR_UNSPEC) {
#if APR_HAVE_IPV6
        family = APR_INET6;
#else
        family = APR_INET;
#endif
    }

    alloc_socket(new, cont);

#ifndef BEOS_R5
    (*new)->socketdes = socket(family, type|flags, protocol);
#else
    /* For some reason BeOS R5 has an unconventional protocol numbering,
     * so we need to translate here. */
    switch (protocol) {
    case 0:
        (*new)->socketdes = socket(family, type|flags, 0);
        break;
    case APR_PROTO_TCP:
        (*new)->socketdes = socket(family, type|flags, IPPROTO_TCP);
        break;
    case APR_PROTO_UDP:
        (*new)->socketdes = socket(family, type|flags, IPPROTO_UDP);
        break;
    case APR_PROTO_SCTP:
    default:
        errno = EPROTONOSUPPORT;
        (*new)->socketdes = -1;
        break;
    }
#endif /* BEOS_R5 */

#if APR_HAVE_IPV6
    if ((*new)->socketdes < 0 && ofamily == APR_UNSPEC) {
        family = APR_INET;
        (*new)->socketdes = socket(family, type|flags, protocol);
    }
#endif

    if ((*new)->socketdes < 0) {
        return errno;
    }
    set_socket_vars(*new, family, type, protocol);

#ifndef HAVE_SOCK_CLOEXEC
    {
        int flags;
        apr_status_t rv;

        if ((flags = fcntl((*new)->socketdes, F_GETFD)) == -1) {
            rv = errno;
            close((*new)->socketdes);
            (*new)->socketdes = -1;
            return rv;
        }

        flags |= FD_CLOEXEC;
        if (fcntl((*new)->socketdes, F_SETFD, flags) == -1) {
            rv = errno;
            close((*new)->socketdes);
            (*new)->socketdes = -1;
            return rv;
        }
    }
#endif

    (*new)->timeout = -1;
    (*new)->inherit = 0;
    apr_pool_cleanup_register((*new)->pool, (void *)(*new), socket_cleanup,
                              socket_cleanup);

    return APR_SUCCESS;
}