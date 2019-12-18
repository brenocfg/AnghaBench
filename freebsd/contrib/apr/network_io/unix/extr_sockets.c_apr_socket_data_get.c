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
struct TYPE_4__ {struct TYPE_4__* next; void* data; int /*<<< orphan*/  key; } ;
typedef  TYPE_1__ sock_userdata_t ;
typedef  int /*<<< orphan*/  apr_status_t ;
struct TYPE_5__ {TYPE_1__* userdata; } ;
typedef  TYPE_2__ apr_socket_t ;

/* Variables and functions */
 int /*<<< orphan*/  APR_SUCCESS ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,char const*) ; 

apr_status_t apr_socket_data_get(void **data, const char *key, apr_socket_t *sock)
{
    sock_userdata_t *cur = sock->userdata;

    *data = NULL;

    while (cur) {
        if (!strcmp(cur->key, key)) {
            *data = cur->data;
            break;
        }
        cur = cur->next;
    }

    return APR_SUCCESS;
}