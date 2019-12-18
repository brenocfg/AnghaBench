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
struct ti_ohci {int /*<<< orphan*/  csr_config_rom_cpu; } ;
struct hpsb_host {struct ti_ohci* hostdata; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int /*<<< orphan*/  OHCI1394_BusOptions ; 
 int /*<<< orphan*/  OHCI1394_ConfigROMhdr ; 
 int /*<<< orphan*/  OHCI_CONFIG_ROM_LEN ; 
 int /*<<< orphan*/  be32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reg_write (struct ti_ohci*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ohci_set_hw_config_rom(struct hpsb_host *host, __be32 *config_rom)
{
	struct ti_ohci *ohci = host->hostdata;

	reg_write(ohci, OHCI1394_ConfigROMhdr, be32_to_cpu(config_rom[0]));
	reg_write(ohci, OHCI1394_BusOptions, be32_to_cpu(config_rom[2]));

	memcpy(ohci->csr_config_rom_cpu, config_rom, OHCI_CONFIG_ROM_LEN);
}