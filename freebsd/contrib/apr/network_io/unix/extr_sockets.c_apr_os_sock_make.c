#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_8__ ;
typedef  struct TYPE_17__   TYPE_6__ ;
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  apr_status_t ;
struct TYPE_16__ {int timeout; int local_port_unknown; int local_interface_unknown; int connected; int remote_addr_unknown; int /*<<< orphan*/  pool; scalar_t__ inherit; TYPE_4__* remote_addr; TYPE_2__* local_addr; int /*<<< orphan*/  socketdes; } ;
typedef  TYPE_5__ apr_socket_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
struct TYPE_17__ {scalar_t__ remote; scalar_t__ local; int /*<<< orphan*/ * os_sock; int /*<<< orphan*/  protocol; int /*<<< orphan*/  type; int /*<<< orphan*/  family; } ;
typedef  TYPE_6__ apr_os_sock_info_t ;
struct TYPE_18__ {int /*<<< orphan*/  sin_port; } ;
struct TYPE_14__ {TYPE_8__ sin; } ;
struct TYPE_15__ {TYPE_3__ sa; void* port; int /*<<< orphan*/  salen; } ;
struct TYPE_12__ {TYPE_8__ sin; } ;
struct TYPE_13__ {TYPE_1__ sa; void* port; int /*<<< orphan*/  salen; } ;

/* Variables and functions */
 int /*<<< orphan*/  APR_SUCCESS ; 
 int /*<<< orphan*/  alloc_socket (TYPE_5__**,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  apr_pool_cleanup_register (int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (TYPE_8__*,scalar_t__,int /*<<< orphan*/ ) ; 
 void* ntohs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_socket_vars (TYPE_5__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  socket_cleanup ; 

apr_status_t apr_os_sock_make(apr_socket_t **apr_sock, 
                              apr_os_sock_info_t *os_sock_info, 
                              apr_pool_t *cont)
{
    alloc_socket(apr_sock, cont);
    set_socket_vars(*apr_sock, os_sock_info->family, os_sock_info->type, os_sock_info->protocol);
    (*apr_sock)->timeout = -1;
    (*apr_sock)->socketdes = *os_sock_info->os_sock;
    if (os_sock_info->local) {
        memcpy(&(*apr_sock)->local_addr->sa.sin, 
               os_sock_info->local, 
               (*apr_sock)->local_addr->salen);
        /* XXX IPv6 - this assumes sin_port and sin6_port at same offset */
        (*apr_sock)->local_addr->port = ntohs((*apr_sock)->local_addr->sa.sin.sin_port);
    }
    else {
        (*apr_sock)->local_port_unknown = (*apr_sock)->local_interface_unknown = 1;
    }
    if (os_sock_info->remote) {
#ifndef HAVE_POLL
        (*apr_sock)->connected = 1;
#endif
        memcpy(&(*apr_sock)->remote_addr->sa.sin, 
               os_sock_info->remote,
               (*apr_sock)->remote_addr->salen);
        /* XXX IPv6 - this assumes sin_port and sin6_port at same offset */
        (*apr_sock)->remote_addr->port = ntohs((*apr_sock)->remote_addr->sa.sin.sin_port);
    }
    else {
        (*apr_sock)->remote_addr_unknown = 1;
    }
        
    (*apr_sock)->inherit = 0;
    apr_pool_cleanup_register((*apr_sock)->pool, (void *)(*apr_sock), 
                              socket_cleanup, socket_cleanup);
    return APR_SUCCESS;
}