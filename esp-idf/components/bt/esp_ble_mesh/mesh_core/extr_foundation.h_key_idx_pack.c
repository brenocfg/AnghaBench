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
struct net_buf_simple {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  net_buf_simple_add_le16 (struct net_buf_simple*,int) ; 
 int /*<<< orphan*/  net_buf_simple_add_u8 (struct net_buf_simple*,int) ; 

__attribute__((used)) static inline void key_idx_pack(struct net_buf_simple *buf,
                                u16_t idx1, u16_t idx2)
{
    net_buf_simple_add_le16(buf, idx1 | ((idx2 & 0x00f) << 12));
    net_buf_simple_add_u8(buf, idx2 >> 4);
}