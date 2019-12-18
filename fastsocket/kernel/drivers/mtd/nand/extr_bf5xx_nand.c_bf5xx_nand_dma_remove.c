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
struct bf5xx_nand_info {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CH_NFC ; 
 int /*<<< orphan*/  free_dma (int /*<<< orphan*/ ) ; 
 scalar_t__ hardware_ecc ; 

__attribute__((used)) static void bf5xx_nand_dma_remove(struct bf5xx_nand_info *info)
{
	/* Free NFC DMA channel */
	if (hardware_ecc)
		free_dma(CH_NFC);
}