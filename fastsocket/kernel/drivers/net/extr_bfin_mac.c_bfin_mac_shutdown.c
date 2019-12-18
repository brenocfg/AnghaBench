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
struct net_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  bfin_write_DMA1_CONFIG (int) ; 
 int /*<<< orphan*/  bfin_write_DMA2_CONFIG (int) ; 
 int /*<<< orphan*/  bfin_write_EMAC_OPMODE (int) ; 

__attribute__((used)) static void bfin_mac_shutdown(struct net_device *dev)
{
	/* Turn off the EMAC */
	bfin_write_EMAC_OPMODE(0x00000000);
	/* Turn off the EMAC RX DMA */
	bfin_write_DMA1_CONFIG(0x0000);
	bfin_write_DMA2_CONFIG(0x0000);
}