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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u64 ;
struct bfa_flash {int /*<<< orphan*/ * dbuf_kva; int /*<<< orphan*/  dbuf_pa; } ;

/* Variables and functions */
 int /*<<< orphan*/  BFA_DMA_ALIGN_SZ ; 
 int /*<<< orphan*/  BFA_FLASH_DMA_BUF_SZ ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ roundup (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
bfa_nw_flash_memclaim(struct bfa_flash *flash, u8 *dm_kva, u64 dm_pa)
{
	flash->dbuf_kva = dm_kva;
	flash->dbuf_pa = dm_pa;
	memset(flash->dbuf_kva, 0, BFA_FLASH_DMA_BUF_SZ);
	dm_kva += roundup(BFA_FLASH_DMA_BUF_SZ, BFA_DMA_ALIGN_SZ);
	dm_pa += roundup(BFA_FLASH_DMA_BUF_SZ, BFA_DMA_ALIGN_SZ);
}