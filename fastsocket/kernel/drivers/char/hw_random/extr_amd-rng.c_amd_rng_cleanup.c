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
typedef  int u8 ;
struct hwrng {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  amd_pdev ; 
 int /*<<< orphan*/  pci_read_config_byte (int /*<<< orphan*/ ,int,int*) ; 
 int /*<<< orphan*/  pci_write_config_byte (int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static void amd_rng_cleanup(struct hwrng *rng)
{
	u8 rnen;

	pci_read_config_byte(amd_pdev, 0x40, &rnen);
	rnen &= ~(1 << 7);	/* RNG off */
	pci_write_config_byte(amd_pdev, 0x40, rnen);
}