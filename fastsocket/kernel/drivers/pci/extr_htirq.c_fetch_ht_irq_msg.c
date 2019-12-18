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
struct ht_irq_msg {int dummy; } ;
struct ht_irq_cfg {struct ht_irq_msg msg; } ;

/* Variables and functions */
 struct ht_irq_cfg* get_irq_data (unsigned int) ; 

void fetch_ht_irq_msg(unsigned int irq, struct ht_irq_msg *msg)
{
	struct ht_irq_cfg *cfg = get_irq_data(irq);
	*msg = cfg->msg;
}