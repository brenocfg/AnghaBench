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
typedef  int uint8_t ;
struct ahc_softc {char channel; int bugs; int instruction_ram_size; int /*<<< orphan*/  features; int /*<<< orphan*/  chip; int /*<<< orphan*/  dev_softc; } ;
typedef  int /*<<< orphan*/  ahc_dev_softc_t ;

/* Variables and functions */
 int /*<<< orphan*/  AHC_AIC7860 ; 
 int /*<<< orphan*/  AHC_AIC7860_FE ; 
 int AHC_CACHETHEN_BUG ; 
 int AHC_PCI_2_1_RETRY_BUG ; 
 int AHC_PCI_MWI_BUG ; 
 int AHC_TMODE_WIDEODD_BUG ; 
 int /*<<< orphan*/  PCIR_REVID ; 
 int ahc_pci_read_config (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
ahc_aic7860_setup(struct ahc_softc *ahc)
{
	ahc_dev_softc_t pci;
	uint8_t rev;

	pci = ahc->dev_softc;
	ahc->channel = 'A';
	ahc->chip = AHC_AIC7860;
	ahc->features = AHC_AIC7860_FE;
	ahc->bugs |= AHC_TMODE_WIDEODD_BUG|AHC_CACHETHEN_BUG|AHC_PCI_MWI_BUG;
	rev = ahc_pci_read_config(pci, PCIR_REVID, /*bytes*/1);
	if (rev >= 1)
		ahc->bugs |= AHC_PCI_2_1_RETRY_BUG;
	ahc->instruction_ram_size = 512;
	return (0);
}