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
struct TYPE_5__ {int timeout; int local_port_unknown; int local_interface_unknown; int remote_addr_unknown; int /*<<< orphan*/  socketdes; } ;
typedef  TYPE_1__ apr_socket_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_os_sock_t ;

/* Variables and functions */
 int /*<<< orphan*/  APR_INET ; 
 int /*<<< orphan*/  APR_SUCCESS ; 
 int /*<<< orphan*/  SOCK_STREAM ; 
 int /*<<< orphan*/  alloc_socket (TYPE_1__**,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_socket_vars (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

apr_status_t apr_os_sock_put(apr_socket_t **sock, apr_os_sock_t *thesock, 
                           apr_pool_t *cont)
{
    /* XXX Bogus assumption that *sock points at anything legit */
    if ((*sock) == NULL) {
        alloc_socket(sock, cont);
        /* XXX IPv6 figure out the family here! */
        /* XXX figure out the actual socket type here */
        /* *or* just decide that apr_os_sock_put() has to be told the family and type */
        set_socket_vars(*sock, APR_INET, SOCK_STREAM, 0);
        (*sock)->timeout = -1;
    }
    (*sock)->local_port_unknown = (*sock)->local_interface_unknown = 1;
    (*sock)->remote_addr_unknown = 1;
    (*sock)->socketdes = *thesock;
    return APR_SUCCESS;
}