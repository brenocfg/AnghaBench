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
struct net_buf {int /*<<< orphan*/  node; int /*<<< orphan*/  flags; struct net_buf* frags; } ;
typedef  struct net_buf sys_slist_t ;

/* Variables and functions */
 int /*<<< orphan*/  NET_BUF_ASSERT (struct net_buf*) ; 
 int /*<<< orphan*/  NET_BUF_FRAGS ; 
 unsigned int bt_mesh_irq_lock () ; 
 int /*<<< orphan*/  bt_mesh_irq_unlock (unsigned int) ; 
 int /*<<< orphan*/  sys_slist_append_list (struct net_buf*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void net_buf_slist_put(sys_slist_t *list, struct net_buf *buf)
{
    struct net_buf *tail;
    unsigned int key;

    NET_BUF_ASSERT(list);
    NET_BUF_ASSERT(buf);

    for (tail = buf; tail->frags; tail = tail->frags) {
        tail->flags |= NET_BUF_FRAGS;
    }

    key = bt_mesh_irq_lock();
    sys_slist_append_list(list, &buf->node, &tail->node);
    bt_mesh_irq_unlock(key);
}