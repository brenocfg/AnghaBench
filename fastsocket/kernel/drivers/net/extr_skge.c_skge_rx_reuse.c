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
struct skge_rx_desc {unsigned int control; int /*<<< orphan*/  csum2_start; scalar_t__ csum2; } ;
struct skge_element {struct skge_rx_desc* desc; } ;

/* Variables and functions */
 unsigned int BMU_IRQ_EOF ; 
 unsigned int BMU_OWN ; 
 unsigned int BMU_STF ; 
 unsigned int BMU_TCP_CHECK ; 
 int /*<<< orphan*/  ETH_HLEN ; 
 int /*<<< orphan*/  wmb () ; 

__attribute__((used)) static inline void skge_rx_reuse(struct skge_element *e, unsigned int size)
{
	struct skge_rx_desc *rd = e->desc;

	rd->csum2 = 0;
	rd->csum2_start = ETH_HLEN;

	wmb();

	rd->control = BMU_OWN | BMU_STF | BMU_IRQ_EOF | BMU_TCP_CHECK | size;
}