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
struct jme_adapter {int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  JME_APMC ; 
 int JME_APMC_EPIEN_CTRL ; 
 int JME_APMC_EPIEN_CTRL_DIS ; 
 int JME_APMC_PCIE_SD_EN ; 
 int /*<<< orphan*/  JME_FLAG_SHUTDOWN ; 
 int /*<<< orphan*/  JME_TIMER2 ; 
 int /*<<< orphan*/  JME_TMCSR ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int jread32 (struct jme_adapter*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jwrite32f (struct jme_adapter*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  wmb () ; 

__attribute__((used)) static void
jme_stop_shutdown_timer(struct jme_adapter *jme)
{
	u32 apmc;

	jwrite32f(jme, JME_TMCSR, 0);
	jwrite32f(jme, JME_TIMER2, 0);
	clear_bit(JME_FLAG_SHUTDOWN, &jme->flags);

	apmc = jread32(jme, JME_APMC);
	apmc &= ~(JME_APMC_PCIE_SD_EN | JME_APMC_EPIEN_CTRL);
	jwrite32f(jme, JME_APMC, apmc | JME_APMC_EPIEN_CTRL_DIS);
	wmb();
	jwrite32f(jme, JME_APMC, apmc);
}