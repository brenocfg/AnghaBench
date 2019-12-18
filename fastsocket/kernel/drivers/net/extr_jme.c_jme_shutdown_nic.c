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
typedef  int u32 ;
struct jme_adapter {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  JME_TIMER2 ; 
 int PHY_LINK_UP ; 
 int TMCSR_EN ; 
 int jme_linkstat_from_phy (struct jme_adapter*) ; 
 int /*<<< orphan*/  jme_stop_irq (struct jme_adapter*) ; 
 int /*<<< orphan*/  jwrite32 (struct jme_adapter*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
jme_shutdown_nic(struct jme_adapter *jme)
{
	u32 phylink;

	phylink = jme_linkstat_from_phy(jme);

	if (!(phylink & PHY_LINK_UP)) {
		/*
		 * Disable all interrupt before issue timer
		 */
		jme_stop_irq(jme);
		jwrite32(jme, JME_TIMER2, TMCSR_EN | 0xFFFFFE);
	}
}