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
typedef  int /*<<< orphan*/  u8_t ;
typedef  int u32_t ;
struct net_buf_simple {int dummy; } ;

/* Variables and functions */
 int ARRAY_SIZE (int*) ; 
 int* dup_cache ; 
 int dup_cache_next ; 
 int /*<<< orphan*/ * net_buf_simple_tail (struct net_buf_simple*) ; 
 int sys_get_be32 (int /*<<< orphan*/  const*) ; 

__attribute__((used)) static bool check_dup(struct net_buf_simple *data)
{
    const u8_t *tail = net_buf_simple_tail(data);
    u32_t val;
    int i;

    val = sys_get_be32(tail - 4) ^ sys_get_be32(tail - 8);

    for (i = 0; i < ARRAY_SIZE(dup_cache); i++) {
        if (dup_cache[i] == val) {
            return true;
        }
    }

    dup_cache[dup_cache_next++] = val;
    dup_cache_next %= ARRAY_SIZE(dup_cache);

    return false;
}