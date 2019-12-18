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
struct cas {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  cas_init_rx_dma (struct cas*) ; 
 int /*<<< orphan*/  cas_init_tx_dma (struct cas*) ; 

__attribute__((used)) static inline void cas_init_dma(struct cas *cp)
{
	cas_init_tx_dma(cp);
	cas_init_rx_dma(cp);
}