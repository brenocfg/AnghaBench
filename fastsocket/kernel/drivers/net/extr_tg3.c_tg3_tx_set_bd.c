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
typedef  int u64 ;
typedef  int u32 ;
struct tg3_tx_buffer_desc {int addr_hi; int addr_lo; int len_flags; int vlan_tag; } ;
typedef  scalar_t__ dma_addr_t ;

/* Variables and functions */
 int TXD_LEN_SHIFT ; 
 int TXD_MSS_SHIFT ; 
 int TXD_VLAN_TAG_SHIFT ; 

__attribute__((used)) static inline void tg3_tx_set_bd(struct tg3_tx_buffer_desc *txbd,
				 dma_addr_t mapping, u32 len, u32 flags,
				 u32 mss, u32 vlan)
{
	txbd->addr_hi = ((u64) mapping >> 32);
	txbd->addr_lo = ((u64) mapping & 0xffffffff);
	txbd->len_flags = (len << TXD_LEN_SHIFT) | (flags & 0x0000ffff);
	txbd->vlan_tag = (mss << TXD_MSS_SHIFT) | (vlan << TXD_VLAN_TAG_SHIFT);
}