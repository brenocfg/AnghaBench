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
typedef  size_t u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct il_tfd_tb {int /*<<< orphan*/  hi_n_len; int /*<<< orphan*/  lo; } ;
struct il_tfd {struct il_tfd_tb* tbs; } ;
typedef  int dma_addr_t ;

/* Variables and functions */
 int get_unaligned_le32 (int /*<<< orphan*/ *) ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline dma_addr_t
il4965_tfd_tb_get_addr(struct il_tfd *tfd, u8 idx)
{
	struct il_tfd_tb *tb = &tfd->tbs[idx];

	dma_addr_t addr = get_unaligned_le32(&tb->lo);
	if (sizeof(dma_addr_t) > sizeof(u32))
		addr |=
		    ((dma_addr_t) (le16_to_cpu(tb->hi_n_len) & 0xF) << 16) <<
		    16;

	return addr;
}