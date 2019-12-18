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
struct linger {int l_onoff; int /*<<< orphan*/  l_linger; } ;
typedef  int /*<<< orphan*/  apr_status_t ;
struct TYPE_5__ {int protocol; int /*<<< orphan*/  socketdes; } ;
typedef  TYPE_1__ apr_socket_t ;
typedef  int apr_int32_t ;

/* Variables and functions */
 int /*<<< orphan*/  APR_EINVAL ; 
 int /*<<< orphan*/  APR_ENOTIMPL ; 
#define  APR_INCOMPLETE_READ 140 
#define  APR_IPV6_V6ONLY 139 
 int /*<<< orphan*/  APR_MAX_SECS_TO_LINGER ; 
 int const APR_RESET_NODELAY ; 
#define  APR_SO_BROADCAST 138 
#define  APR_SO_DEBUG 137 
#define  APR_SO_KEEPALIVE 136 
#define  APR_SO_LINGER 135 
#define  APR_SO_NONBLOCK 134 
#define  APR_SO_RCVBUF 133 
#define  APR_SO_REUSEADDR 132 
#define  APR_SO_SNDBUF 131 
 int /*<<< orphan*/  APR_SUCCESS ; 
#define  APR_TCP_DEFER_ACCEPT 130 
#define  APR_TCP_NODELAY 129 
#define  APR_TCP_NOPUSH 128 
 int APR_TCP_NOPUSH_FLAG ; 
 int IPPROTO_IPV6 ; 
 int IPPROTO_SCTP ; 
 int IPPROTO_TCP ; 
 int IPV6_V6ONLY ; 
 int SCTP_NODELAY ; 
 int SOL_SOCKET ; 
 int SO_BROADCAST ; 
 int SO_DEBUG ; 
 int SO_KEEPALIVE ; 
 int /*<<< orphan*/  SO_LINGER ; 
 int SO_RCVBUF ; 
 int SO_REUSEADDR ; 
 int SO_SNDBUF ; 
 int TCP_DEFER_ACCEPT ; 
 int TCP_NODELAY ; 
 int apr_is_option_set (TYPE_1__*,int const) ; 
 int /*<<< orphan*/  apr_set_option (TYPE_1__*,int const,int) ; 
 int /*<<< orphan*/  errno ; 
 int setsockopt (int /*<<< orphan*/ ,int,int,void*,int) ; 
 int /*<<< orphan*/  soblock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sononblock (int /*<<< orphan*/ ) ; 

apr_status_t apr_socket_opt_set(apr_socket_t *sock, 
                                apr_int32_t opt, apr_int32_t on)
{
    int one;
    apr_status_t rv;

    if (on)
        one = 1;
    else
        one = 0;
    switch(opt) {
    case APR_SO_KEEPALIVE:
#ifdef SO_KEEPALIVE
        if (on != apr_is_option_set(sock, APR_SO_KEEPALIVE)) {
            if (setsockopt(sock->socketdes, SOL_SOCKET, SO_KEEPALIVE, (void *)&one, sizeof(int)) == -1) {
                return errno;
            }
            apr_set_option(sock, APR_SO_KEEPALIVE, on);
        }
#else
        return APR_ENOTIMPL;
#endif
        break;
    case APR_SO_DEBUG:
        if (on != apr_is_option_set(sock, APR_SO_DEBUG)) {
            if (setsockopt(sock->socketdes, SOL_SOCKET, SO_DEBUG, (void *)&one, sizeof(int)) == -1) {
                return errno;
            }
            apr_set_option(sock, APR_SO_DEBUG, on);
        }
        break;
    case APR_SO_BROADCAST:
#ifdef SO_BROADCAST
        if (on != apr_is_option_set(sock, APR_SO_BROADCAST)) {
            if (setsockopt(sock->socketdes, SOL_SOCKET, SO_BROADCAST, (void *)&one, sizeof(int)) == -1) {
                return errno;
            }
            apr_set_option(sock, APR_SO_BROADCAST, on);
        }
#else
        return APR_ENOTIMPL;
#endif
        break;
    case APR_SO_REUSEADDR:
        if (on != apr_is_option_set(sock, APR_SO_REUSEADDR)) {
            if (setsockopt(sock->socketdes, SOL_SOCKET, SO_REUSEADDR, (void *)&one, sizeof(int)) == -1) {
                return errno;
            }
            apr_set_option(sock, APR_SO_REUSEADDR, on);
        }
        break;
    case APR_SO_SNDBUF:
#ifdef SO_SNDBUF
        if (setsockopt(sock->socketdes, SOL_SOCKET, SO_SNDBUF, (void *)&on, sizeof(int)) == -1) {
            return errno;
        }
#else
        return APR_ENOTIMPL;
#endif
        break;
    case APR_SO_RCVBUF:
#ifdef SO_RCVBUF
        if (setsockopt(sock->socketdes, SOL_SOCKET, SO_RCVBUF, (void *)&on, sizeof(int)) == -1) {
            return errno;
        }
#else
        return APR_ENOTIMPL;
#endif
        break;
    case APR_SO_NONBLOCK:
        if (apr_is_option_set(sock, APR_SO_NONBLOCK) != on) {
            if (on) {
                if ((rv = sononblock(sock->socketdes)) != APR_SUCCESS) 
                    return rv;
            }
            else {
                if ((rv = soblock(sock->socketdes)) != APR_SUCCESS)
                    return rv;
            }
            apr_set_option(sock, APR_SO_NONBLOCK, on);
        }
        break;
    case APR_SO_LINGER:
#ifdef SO_LINGER
        if (apr_is_option_set(sock, APR_SO_LINGER) != on) {
            struct linger li;
            li.l_onoff = on;
            li.l_linger = APR_MAX_SECS_TO_LINGER;
            if (setsockopt(sock->socketdes, SOL_SOCKET, SO_LINGER, (char *) &li, sizeof(struct linger)) == -1) {
                return errno;
            }
            apr_set_option(sock, APR_SO_LINGER, on);
        }
#else
        return APR_ENOTIMPL;
#endif
        break;
    case APR_TCP_DEFER_ACCEPT:
#if defined(TCP_DEFER_ACCEPT)
        if (apr_is_option_set(sock, APR_TCP_DEFER_ACCEPT) != on) {
            int optlevel = IPPROTO_TCP;
            int optname = TCP_DEFER_ACCEPT;

            if (setsockopt(sock->socketdes, optlevel, optname, 
                           (void *)&on, sizeof(int)) == -1) {
                return errno;
            }
            apr_set_option(sock, APR_TCP_DEFER_ACCEPT, on);
        }
#else
        return APR_ENOTIMPL;
#endif
        break;
    case APR_TCP_NODELAY:
#if defined(TCP_NODELAY)
        if (apr_is_option_set(sock, APR_TCP_NODELAY) != on) {
            int optlevel = IPPROTO_TCP;
            int optname = TCP_NODELAY;

#if APR_HAVE_SCTP
            if (sock->protocol == IPPROTO_SCTP) {
                optlevel = IPPROTO_SCTP;
                optname = SCTP_NODELAY;
            }
#endif
            if (setsockopt(sock->socketdes, optlevel, optname, (void *)&on, sizeof(int)) == -1) {
                return errno;
            }
            apr_set_option(sock, APR_TCP_NODELAY, on);
        }
#else
        /* BeOS pre-BONE has TCP_NODELAY set by default.
         * As it can't be turned off we might as well check if they're asking
         * for it to be turned on!
         */
#ifdef BEOS
        if (on == 1)
            return APR_SUCCESS;
        else
#endif
        return APR_ENOTIMPL;
#endif
        break;
    case APR_TCP_NOPUSH:
#if APR_TCP_NOPUSH_FLAG
        /* TCP_NODELAY and TCP_CORK are mutually exclusive on Linux
         * kernels < 2.6; on newer kernels they can be used together
         * and TCP_CORK takes preference, which is the desired
         * behaviour.  On older kernels, TCP_NODELAY must be toggled
         * to "off" whilst TCP_CORK is in effect. */
        if (apr_is_option_set(sock, APR_TCP_NOPUSH) != on) {
#ifndef HAVE_TCP_NODELAY_WITH_CORK
            int optlevel = IPPROTO_TCP;
            int optname = TCP_NODELAY;

#if APR_HAVE_SCTP
            if (sock->protocol == IPPROTO_SCTP) {
                optlevel = IPPROTO_SCTP;
                optname = SCTP_NODELAY;
            }
#endif
            /* OK we're going to change some settings here... */
            if (apr_is_option_set(sock, APR_TCP_NODELAY) == 1 && on) {
                /* Now toggle TCP_NODELAY to off, if TCP_CORK is being
                 * turned on: */
                int tmpflag = 0;
                if (setsockopt(sock->socketdes, optlevel, optname,
                               (void*)&tmpflag, sizeof(int)) == -1) {
                    return errno;
                }
                apr_set_option(sock, APR_RESET_NODELAY, 1);
                apr_set_option(sock, APR_TCP_NODELAY, 0);
            } else if (on) {
                apr_set_option(sock, APR_RESET_NODELAY, 0);
            }
#endif /* HAVE_TCP_NODELAY_WITH_CORK */

            /* OK, now we can just set the TCP_NOPUSH flag accordingly...*/
            if (setsockopt(sock->socketdes, IPPROTO_TCP, APR_TCP_NOPUSH_FLAG,
                           (void*)&on, sizeof(int)) == -1) {
                return errno;
            }
            apr_set_option(sock, APR_TCP_NOPUSH, on);
#ifndef HAVE_TCP_NODELAY_WITH_CORK
            if (!on && apr_is_option_set(sock, APR_RESET_NODELAY)) {
                /* Now, if TCP_CORK was just turned off, turn
                 * TCP_NODELAY back on again if it was earlier toggled
                 * to off: */
                int tmpflag = 1;
                if (setsockopt(sock->socketdes, optlevel, optname,
                               (void*)&tmpflag, sizeof(int)) == -1) {
                    return errno;
                }
                apr_set_option(sock, APR_RESET_NODELAY,0);
                apr_set_option(sock, APR_TCP_NODELAY, 1);
            }
#endif /* HAVE_TCP_NODELAY_WITH_CORK */
        }
#else
        return APR_ENOTIMPL;
#endif
        break;
    case APR_INCOMPLETE_READ:
        apr_set_option(sock, APR_INCOMPLETE_READ, on);
        break;
    case APR_IPV6_V6ONLY:
#if APR_HAVE_IPV6 && defined(IPV6_V6ONLY)
        /* we don't know the initial setting of this option,
         * so don't check sock->options since that optimization
         * won't work
         */
        if (setsockopt(sock->socketdes, IPPROTO_IPV6, IPV6_V6ONLY,
                       (void *)&on, sizeof(int)) == -1) {
            return errno;
        }
        apr_set_option(sock, APR_IPV6_V6ONLY, on);
#else
        return APR_ENOTIMPL;
#endif
        break;
    default:
        return APR_EINVAL;
    }

    return APR_SUCCESS; 
}