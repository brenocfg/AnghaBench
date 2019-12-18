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
struct r8192_priv {TYPE_1__* ieee80211; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int IMR_RDU ; 
 int /*<<< orphan*/  INTA_MASK ; 
 int read_nic_dword (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtl8192_rx (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_nic_dword (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

void rtl8192_irq_rx_tasklet(struct r8192_priv *priv)
{
       rtl8192_rx(priv->ieee80211->dev);
	/* unmask RDU */
       write_nic_dword(priv->ieee80211->dev, INTA_MASK,read_nic_dword(priv->ieee80211->dev, INTA_MASK) | IMR_RDU);
}