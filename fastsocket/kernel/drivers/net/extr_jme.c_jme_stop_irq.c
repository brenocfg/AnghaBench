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
struct jme_adapter {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  INTR_ENABLE ; 
 int /*<<< orphan*/  JME_IENC ; 
 int /*<<< orphan*/  jwrite32f (struct jme_adapter*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void
jme_stop_irq(struct jme_adapter *jme)
{
	/*
	 * Disable Interrupts
	 */
	jwrite32f(jme, JME_IENC, INTR_ENABLE);
}