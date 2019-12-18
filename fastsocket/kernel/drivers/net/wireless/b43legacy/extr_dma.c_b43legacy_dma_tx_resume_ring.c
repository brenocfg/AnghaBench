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
struct b43legacy_dmaring {int /*<<< orphan*/  tx; } ;

/* Variables and functions */
 int /*<<< orphan*/  B43legacy_WARN_ON (int) ; 
 int /*<<< orphan*/  op32_tx_resume (struct b43legacy_dmaring*) ; 

__attribute__((used)) static void b43legacy_dma_tx_resume_ring(struct b43legacy_dmaring *ring)
{
	B43legacy_WARN_ON(!ring->tx);
	op32_tx_resume(ring);
}