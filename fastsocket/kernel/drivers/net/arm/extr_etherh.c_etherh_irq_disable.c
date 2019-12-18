#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct etherh_priv {int dummy; } ;
struct TYPE_3__ {struct etherh_priv* irq_data; } ;
typedef  TYPE_1__ ecard_t ;

/* Variables and functions */
 int /*<<< orphan*/  ETHERH_CP_IE ; 
 int /*<<< orphan*/  etherh_clr_ctrl (struct etherh_priv*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void etherh_irq_disable(ecard_t *ec, int irqnr)
{
	struct etherh_priv *eh = ec->irq_data;

	etherh_clr_ctrl(eh, ETHERH_CP_IE);
}