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
struct net_buf {int flags; struct net_buf* frags; } ;
typedef  struct net_buf sys_slist_t ;

/* Variables and functions */
 int /*<<< orphan*/  NET_BUF_ASSERT (struct net_buf*) ; 
 int NET_BUF_FRAGS ; 
 unsigned int bt_mesh_irq_lock () ; 
 int /*<<< orphan*/  bt_mesh_irq_unlock (unsigned int) ; 
 scalar_t__ sys_slist_get (struct net_buf*) ; 

struct net_buf *net_buf_slist_get(sys_slist_t *list)
{
    struct net_buf *buf, *frag;
    unsigned int key;

    NET_BUF_ASSERT(list);

    key = bt_mesh_irq_lock();
    buf = (void *)sys_slist_get(list);
    bt_mesh_irq_unlock(key);

    if (!buf) {
        return NULL;
    }

    /* Get any fragments belonging to this buffer */
    for (frag = buf; (frag->flags & NET_BUF_FRAGS); frag = frag->frags) {
        key = bt_mesh_irq_lock();
        frag->frags = (void *)sys_slist_get(list);
        bt_mesh_irq_unlock(key);

        NET_BUF_ASSERT(frag->frags);

        /* The fragments flag is only for list-internal usage */
        frag->flags &= ~NET_BUF_FRAGS;
    }

    /* Mark the end of the fragment list */
    frag->frags = NULL;

    return buf;
}