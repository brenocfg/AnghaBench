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
struct sockaddr_storage {int nodeid; int addr_count; struct sockaddr_storage** addr; int /*<<< orphan*/  list; } ;
struct dlm_node_addr {int nodeid; int addr_count; struct dlm_node_addr** addr; int /*<<< orphan*/  list; } ;

/* Variables and functions */
 scalar_t__ DLM_MAX_ADDR_COUNT ; 
 int ENOMEM ; 
 int ENOSPC ; 
 int /*<<< orphan*/  GFP_NOFS ; 
 int /*<<< orphan*/  dlm_node_addrs ; 
 int /*<<< orphan*/  dlm_node_addrs_spin ; 
 struct sockaddr_storage* find_node_addr (int) ; 
 int /*<<< orphan*/  kfree (struct sockaddr_storage*) ; 
 struct sockaddr_storage* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (struct sockaddr_storage*,struct sockaddr_storage*,int) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

int dlm_lowcomms_addr(int nodeid, struct sockaddr_storage *addr, int len)
{
        struct sockaddr_storage *new_addr;
        struct dlm_node_addr *new_node, *na;

        new_node = kzalloc(sizeof(struct dlm_node_addr), GFP_NOFS);
        if (!new_node)
                return -ENOMEM;

        new_addr = kzalloc(sizeof(struct sockaddr_storage), GFP_NOFS);
        if (!new_addr) {
                kfree(new_node);
                return -ENOMEM;
        }

        memcpy(new_addr, addr, len);

        spin_lock(&dlm_node_addrs_spin);
        na = find_node_addr(nodeid);
        if (!na) {
                new_node->nodeid = nodeid;
                new_node->addr[0] = new_addr;
                new_node->addr_count = 1;
                list_add(&new_node->list, &dlm_node_addrs);
                spin_unlock(&dlm_node_addrs_spin);
                return 0;
        }

        if (na->addr_count >= DLM_MAX_ADDR_COUNT) {
                spin_unlock(&dlm_node_addrs_spin);
                kfree(new_addr);
                kfree(new_node);
                return -ENOSPC;
        }

        na->addr[na->addr_count++] = new_addr;
        spin_unlock(&dlm_node_addrs_spin);
        kfree(new_node);
        return 0;
}