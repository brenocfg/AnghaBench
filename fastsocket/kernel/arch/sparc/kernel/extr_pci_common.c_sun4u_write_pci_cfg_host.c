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
typedef  int /*<<< orphan*/  u8 ;
typedef  int u32 ;
typedef  int u16 ;
struct pci_pbm_info {int dummy; } ;

/* Variables and functions */
 int PCIBIOS_SUCCESSFUL ; 
 int /*<<< orphan*/  pci_config_read16 (int*,int*) ; 
 int /*<<< orphan*/  pci_config_write16 (int*,int) ; 
 int /*<<< orphan*/  pci_config_write8 (int /*<<< orphan*/ *,int) ; 
 int* sun4u_config_mkaddr (struct pci_pbm_info*,unsigned char,unsigned int,int) ; 

__attribute__((used)) static int sun4u_write_pci_cfg_host(struct pci_pbm_info *pbm,
				    unsigned char bus, unsigned int devfn,
				    int where, int size, u32 value)
{
	u32 *addr;

	addr = sun4u_config_mkaddr(pbm, bus, devfn, where);
	if (!addr)
		return PCIBIOS_SUCCESSFUL;

	switch (size) {
	case 1:
		if (where < 8) {
			unsigned long align = (unsigned long) addr;
			u16 tmp16;

			align &= ~1;
			pci_config_read16((u16 *)align, &tmp16);
			if (where & 1) {
				tmp16 &= 0x00ff;
				tmp16 |= value << 8;
			} else {
				tmp16 &= 0xff00;
				tmp16 |= value;
			}
			pci_config_write16((u16 *)align, tmp16);
		} else
			pci_config_write8((u8 *)addr, value);
		break;
	case 2:
		if (where < 8) {
			pci_config_write16((u16 *)addr, value);
		} else {
			pci_config_write8((u8 *)addr, value & 0xff);
			pci_config_write8(((u8 *)addr) + 1, value >> 8);
		}
		break;
	case 4:
		sun4u_write_pci_cfg_host(pbm, bus, devfn,
					 where, 2, value & 0xffff);
		sun4u_write_pci_cfg_host(pbm, bus, devfn,
					 where + 2, 2, value >> 16);
		break;
	}
	return PCIBIOS_SUCCESSFUL;
}