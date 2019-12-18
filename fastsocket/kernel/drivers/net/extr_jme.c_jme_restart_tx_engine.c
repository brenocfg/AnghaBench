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
struct jme_adapter {int reg_txcs; } ;

/* Variables and functions */
 int /*<<< orphan*/  JME_TXCS ; 
 int TXCS_ENABLE ; 
 int TXCS_SELECT_QUEUE0 ; 
 int /*<<< orphan*/  jwrite32 (struct jme_adapter*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static inline void
jme_restart_tx_engine(struct jme_adapter *jme)
{
	/*
	 * Restart TX Engine
	 */
	jwrite32(jme, JME_TXCS, jme->reg_txcs |
				TXCS_SELECT_QUEUE0 |
				TXCS_ENABLE);
}