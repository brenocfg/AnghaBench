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
struct TYPE_4__ {int remote_addr_unknown; int /*<<< orphan*/  pollset; TYPE_2__* remote_addr; int /*<<< orphan*/ * pool; TYPE_2__* local_addr; } ;
typedef  TYPE_1__ apr_socket_t ;
struct TYPE_5__ {int /*<<< orphan*/ * pool; } ;
typedef  TYPE_2__ apr_sockaddr_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 scalar_t__ apr_pcalloc (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  apr_pollset_create (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void alloc_socket(apr_socket_t **new, apr_pool_t *p)
{
    *new = (apr_socket_t *)apr_pcalloc(p, sizeof(apr_socket_t));
    (*new)->pool = p;
    (*new)->local_addr = (apr_sockaddr_t *)apr_pcalloc((*new)->pool,
                                                       sizeof(apr_sockaddr_t));
    (*new)->local_addr->pool = p;
    (*new)->remote_addr = (apr_sockaddr_t *)apr_pcalloc((*new)->pool,
                                                        sizeof(apr_sockaddr_t));
    (*new)->remote_addr->pool = p;
    (*new)->remote_addr_unknown = 1;
#ifndef WAITIO_USES_POLL
    /* Create a pollset with room for one descriptor. */
    /* ### check return codes */
    (void) apr_pollset_create(&(*new)->pollset, 1, p, 0);
#endif
}