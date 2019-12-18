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
struct sja1000_priv {scalar_t__ priv; } ;
struct ems_pci_card {scalar_t__ conf_addr; } ;

/* Variables and functions */
 scalar_t__ PLX_ICSR ; 
 int /*<<< orphan*/  PLX_ICSR_ENA_CLR ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void ems_pci_v2_post_irq(const struct sja1000_priv *priv)
{
	struct ems_pci_card *card = (struct ems_pci_card *)priv->priv;

	writel(PLX_ICSR_ENA_CLR, card->conf_addr + PLX_ICSR);
}