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
typedef  int /*<<< orphan*/  u32 ;
struct mpsc_tx_desc {int dummy; } ;
struct mpsc_port_info {scalar_t__ sdma_base; } ;

/* Variables and functions */
 scalar_t__ SDMA_SCTDP ; 
 scalar_t__ SDMA_SFTDP ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void mpsc_sdma_set_tx_ring(struct mpsc_port_info *pi,
		struct mpsc_tx_desc *txre_p)
{
	writel((u32)txre_p, pi->sdma_base + SDMA_SFTDP);
	writel((u32)txre_p, pi->sdma_base + SDMA_SCTDP);
}