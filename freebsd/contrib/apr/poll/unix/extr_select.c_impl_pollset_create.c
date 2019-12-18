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
typedef  int apr_uint32_t ;
typedef  int /*<<< orphan*/  apr_status_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
struct TYPE_5__ {TYPE_1__* p; } ;
typedef  TYPE_2__ apr_pollset_t ;
typedef  int /*<<< orphan*/  apr_pollset_private_t ;
typedef  int /*<<< orphan*/  apr_pollfd_t ;
struct TYPE_4__ {void* result_set; void* query_set; int /*<<< orphan*/  set_type; scalar_t__ maxfd; int /*<<< orphan*/  exceptset; int /*<<< orphan*/  writeset; int /*<<< orphan*/  readset; } ;

/* Variables and functions */
 int /*<<< orphan*/  APR_EINVAL ; 
 int /*<<< orphan*/  APR_ENOTIMPL ; 
 int /*<<< orphan*/  APR_NO_DESC ; 
 int APR_POLLSET_THREADSAFE ; 
 int /*<<< orphan*/  APR_SUCCESS ; 
 int FD_SETSIZE ; 
 int /*<<< orphan*/  FD_ZERO (int /*<<< orphan*/ *) ; 
 void* apr_palloc (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static apr_status_t impl_pollset_create(apr_pollset_t *pollset,
                                        apr_uint32_t size,
                                        apr_pool_t *p,
                                        apr_uint32_t flags)
{
    if (flags & APR_POLLSET_THREADSAFE) {                
        pollset->p = NULL;
        return APR_ENOTIMPL;
    }
#ifdef FD_SETSIZE
    if (size > FD_SETSIZE) {
        pollset->p = NULL;
        return APR_EINVAL;
    }
#endif
    pollset->p = apr_palloc(p, sizeof(apr_pollset_private_t));
    FD_ZERO(&(pollset->p->readset));
    FD_ZERO(&(pollset->p->writeset));
    FD_ZERO(&(pollset->p->exceptset));
    pollset->p->maxfd = 0;
#ifdef NETWARE
    pollset->p->set_type = APR_NO_DESC;
#endif
    pollset->p->query_set = apr_palloc(p, size * sizeof(apr_pollfd_t));
    pollset->p->result_set = apr_palloc(p, size * sizeof(apr_pollfd_t));

    return APR_SUCCESS;
}