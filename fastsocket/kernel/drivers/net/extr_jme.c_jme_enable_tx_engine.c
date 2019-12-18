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
struct jme_adapter {int tx_ring_size; int reg_txcs; TYPE_1__* txring; } ;
typedef  int __u64 ;
struct TYPE_2__ {scalar_t__ dma; } ;

/* Variables and functions */
 int /*<<< orphan*/  JME_TXCS ; 
 int /*<<< orphan*/  JME_TXDBA_HI ; 
 int /*<<< orphan*/  JME_TXDBA_LO ; 
 int /*<<< orphan*/  JME_TXNDA ; 
 int /*<<< orphan*/  JME_TXQDC ; 
 int TXCS_DEFAULT ; 
 int TXCS_ENABLE ; 
 int TXCS_SELECT_QUEUE0 ; 
 int /*<<< orphan*/  jwrite32 (struct jme_adapter*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  wmb () ; 

__attribute__((used)) static inline void
jme_enable_tx_engine(struct jme_adapter *jme)
{
	/*
	 * Select Queue 0
	 */
	jwrite32(jme, JME_TXCS, TXCS_DEFAULT | TXCS_SELECT_QUEUE0);
	wmb();

	/*
	 * Setup TX Queue 0 DMA Bass Address
	 */
	jwrite32(jme, JME_TXDBA_LO, (__u64)jme->txring[0].dma & 0xFFFFFFFFUL);
	jwrite32(jme, JME_TXDBA_HI, (__u64)(jme->txring[0].dma) >> 32);
	jwrite32(jme, JME_TXNDA, (__u64)jme->txring[0].dma & 0xFFFFFFFFUL);

	/*
	 * Setup TX Descptor Count
	 */
	jwrite32(jme, JME_TXQDC, jme->tx_ring_size);

	/*
	 * Enable TX Engine
	 */
	wmb();
	jwrite32(jme, JME_TXCS, jme->reg_txcs |
				TXCS_SELECT_QUEUE0 |
				TXCS_ENABLE);

}