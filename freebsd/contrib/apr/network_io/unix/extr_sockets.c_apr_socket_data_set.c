#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {struct TYPE_5__* next; void* data; int /*<<< orphan*/  key; } ;
typedef  TYPE_1__ sock_userdata_t ;
typedef  int /*<<< orphan*/  apr_status_t ;
struct TYPE_6__ {int /*<<< orphan*/  pool; TYPE_1__* userdata; } ;
typedef  TYPE_2__ apr_socket_t ;

/* Variables and functions */
 int /*<<< orphan*/  APR_SUCCESS ; 
 TYPE_1__* apr_palloc (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  apr_pool_cleanup_register (int /*<<< orphan*/ ,void*,int /*<<< orphan*/  (*) (void*),int /*<<< orphan*/  (*) (void*)) ; 
 int /*<<< orphan*/  apr_pstrdup (int /*<<< orphan*/ ,char const*) ; 

apr_status_t apr_socket_data_set(apr_socket_t *sock, void *data, const char *key,
                                 apr_status_t (*cleanup) (void *))
{
    sock_userdata_t *new = apr_palloc(sock->pool, sizeof(sock_userdata_t));

    new->key = apr_pstrdup(sock->pool, key);
    new->data = data;
    new->next = sock->userdata;
    sock->userdata = new;

    if (cleanup) {
        apr_pool_cleanup_register(sock->pool, data, cleanup, cleanup);
    }

    return APR_SUCCESS;
}