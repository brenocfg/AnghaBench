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
typedef  int /*<<< orphan*/  apr_pollset_provider_t ;
typedef  int apr_pollset_method_e ;

/* Variables and functions */
#define  APR_POLLSET_AIO_MSGQ 134 
#define  APR_POLLSET_DEFAULT 133 
#define  APR_POLLSET_EPOLL 132 
#define  APR_POLLSET_KQUEUE 131 
#define  APR_POLLSET_POLL 130 
#define  APR_POLLSET_PORT 129 
#define  APR_POLLSET_SELECT 128 
 int /*<<< orphan*/ * apr_pollset_provider_aio_msgq ; 
 int /*<<< orphan*/ * apr_pollset_provider_epoll ; 
 int /*<<< orphan*/ * apr_pollset_provider_kqueue ; 
 int /*<<< orphan*/ * apr_pollset_provider_poll ; 
 int /*<<< orphan*/ * apr_pollset_provider_port ; 
 int /*<<< orphan*/ * apr_pollset_provider_select ; 

__attribute__((used)) static apr_pollset_provider_t *pollset_provider(apr_pollset_method_e method)
{
    apr_pollset_provider_t *provider = NULL;
    switch (method) {
        case APR_POLLSET_KQUEUE:
#if defined(HAVE_KQUEUE)
            provider = apr_pollset_provider_kqueue;
#endif
        break;
        case APR_POLLSET_PORT:
#if defined(HAVE_PORT_CREATE)
            provider = apr_pollset_provider_port;
#endif
        break;
        case APR_POLLSET_EPOLL:
#if defined(HAVE_EPOLL)
            provider = apr_pollset_provider_epoll;
#endif
        break;
        case APR_POLLSET_AIO_MSGQ:
#if defined(HAVE_AIO_MSGQ)
            provider = apr_pollset_provider_aio_msgq;
#endif
        break;
        case APR_POLLSET_POLL:
#if defined(HAVE_POLL)
            provider = apr_pollset_provider_poll;
#endif
        break;
        case APR_POLLSET_SELECT:
            provider = apr_pollset_provider_select;
        break;
        case APR_POLLSET_DEFAULT:
        break;
    }
    return provider;
}