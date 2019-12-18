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
struct jme_adapter {int reg_rxcs; } ;

/* Variables and functions */
 int /*<<< orphan*/  JME_RXCS ; 
 int RXCS_ENABLE ; 
 int RXCS_QST ; 
 int RXCS_QUEUESEL_Q0 ; 
 int /*<<< orphan*/  jwrite32 (struct jme_adapter*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static inline void
jme_restart_rx_engine(struct jme_adapter *jme)
{
	/*
	 * Start RX Engine
	 */
	jwrite32(jme, JME_RXCS, jme->reg_rxcs |
				RXCS_QUEUESEL_Q0 |
				RXCS_ENABLE |
				RXCS_QST);
}