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
typedef  scalar_t__ u64_t ;
typedef  size_t u16_t ;
struct net_buf_simple {int dummy; } ;
struct bt_mesh_net_rx {size_t msg_cache_idx; } ;

/* Variables and functions */
 size_t ARRAY_SIZE (scalar_t__*) ; 
 scalar_t__* msg_cache ; 
 size_t msg_cache_next ; 
 scalar_t__ msg_hash (struct bt_mesh_net_rx*,struct net_buf_simple*) ; 

__attribute__((used)) static bool msg_cache_match(struct bt_mesh_net_rx *rx,
                            struct net_buf_simple *pdu)
{
    u64_t hash = msg_hash(rx, pdu);
    u16_t i;

    for (i = 0U; i < ARRAY_SIZE(msg_cache); i++) {
        if (msg_cache[i] == hash) {
            return true;
        }
    }

    /* Add to the cache */
    rx->msg_cache_idx = msg_cache_next++;
    msg_cache[rx->msg_cache_idx] = hash;
    msg_cache_next %= ARRAY_SIZE(msg_cache);

    return false;
}