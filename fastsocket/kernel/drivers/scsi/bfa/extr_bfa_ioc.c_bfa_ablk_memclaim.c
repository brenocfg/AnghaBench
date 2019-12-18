#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u64 ;
struct TYPE_2__ {int /*<<< orphan*/  pa; int /*<<< orphan*/ * kva; } ;
struct bfa_ablk_s {TYPE_1__ dma_addr; } ;

/* Variables and functions */

void
bfa_ablk_memclaim(struct bfa_ablk_s *ablk, u8 *dma_kva, u64 dma_pa)
{
	ablk->dma_addr.kva = dma_kva;
	ablk->dma_addr.pa  = dma_pa;
}