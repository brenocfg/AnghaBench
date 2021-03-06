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
typedef  int u16_t ;
struct net_buf_simple {int /*<<< orphan*/ * data; } ;

/* Variables and functions */
 int /*<<< orphan*/  net_buf_simple_pull (struct net_buf_simple*,int) ; 
 int sys_get_le16 (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void key_idx_unpack(struct net_buf_simple *buf,
                                  u16_t *idx1, u16_t *idx2)
{
    *idx1 = sys_get_le16(&buf->data[0]) & 0xfff;
    *idx2 = sys_get_le16(&buf->data[1]) >> 4;
    net_buf_simple_pull(buf, 3);
}