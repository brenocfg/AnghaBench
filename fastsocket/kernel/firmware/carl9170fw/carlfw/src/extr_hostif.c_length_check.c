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
struct dma_desc {int totalLen; } ;
struct TYPE_2__ {int len; } ;
struct carl9170_tx_superframe {TYPE_1__ s; } ;
struct carl9170_tx_superdesc {int dummy; } ;

/* Variables and functions */
 struct carl9170_tx_superframe* __get_super (struct dma_desc*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static bool length_check(struct dma_desc *desc)
{
	volatile struct carl9170_tx_superframe *super = __get_super(desc);

	if (unlikely(desc->totalLen < sizeof(struct carl9170_tx_superdesc)))
		return false;

	/*
	 * check if the DMA is complete, or clipped.
	 *
	 * NB: The hardware aligns the descriptor length to
	 * a 4 byte boundary. This makes the direct comparison
	 * difficult, or unnecessary complex for a hot-path.
	 */
	if (unlikely(super->s.len > desc->totalLen))
		return false;

	return true;
}