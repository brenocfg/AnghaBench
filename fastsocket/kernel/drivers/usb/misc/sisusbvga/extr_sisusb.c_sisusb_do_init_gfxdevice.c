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
typedef  int u32 ;
struct sisusb_usb_data {int dummy; } ;
struct sisusb_packet {int header; int address; int data; } ;

/* Variables and functions */
 int SISUSB_PCI_IOPORTBASE ; 
 int SISUSB_PCI_MEMBASE ; 
 int SISUSB_PCI_MMIOBASE ; 
 int sisusb_read_pci_config (struct sisusb_usb_data*,int,int*) ; 
 int sisusb_send_bridge_packet (struct sisusb_usb_data*,int,struct sisusb_packet*,int /*<<< orphan*/ ) ; 
 int sisusb_write_pci_config (struct sisusb_usb_data*,int,int) ; 

__attribute__((used)) static int
sisusb_do_init_gfxdevice(struct sisusb_usb_data *sisusb)
{
	struct sisusb_packet packet;
	int ret;
	u32 tmp32;

	/* Do some magic */
	packet.header  = 0x001f;
	packet.address = 0x00000324;
	packet.data    = 0x00000004;
	ret = sisusb_send_bridge_packet(sisusb, 10, &packet, 0);

	packet.header  = 0x001f;
	packet.address = 0x00000364;
	packet.data    = 0x00000004;
	ret |= sisusb_send_bridge_packet(sisusb, 10, &packet, 0);

	packet.header  = 0x001f;
	packet.address = 0x00000384;
	packet.data    = 0x00000004;
	ret |= sisusb_send_bridge_packet(sisusb, 10, &packet, 0);

	packet.header  = 0x001f;
	packet.address = 0x00000100;
	packet.data    = 0x00000700;
	ret |= sisusb_send_bridge_packet(sisusb, 10, &packet, 0);

	packet.header  = 0x000f;
	packet.address = 0x00000004;
	ret |= sisusb_send_bridge_packet(sisusb, 6, &packet, 0);
	packet.data |= 0x17;
	ret |= sisusb_send_bridge_packet(sisusb, 10, &packet, 0);

	/* Init BAR 0 (VRAM) */
	ret |= sisusb_read_pci_config(sisusb, 0x10, &tmp32);
	ret |= sisusb_write_pci_config(sisusb, 0x10, 0xfffffff0);
	ret |= sisusb_read_pci_config(sisusb, 0x10, &tmp32);
	tmp32 &= 0x0f;
	tmp32 |= SISUSB_PCI_MEMBASE;
	ret |= sisusb_write_pci_config(sisusb, 0x10, tmp32);

	/* Init BAR 1 (MMIO) */
	ret |= sisusb_read_pci_config(sisusb, 0x14, &tmp32);
	ret |= sisusb_write_pci_config(sisusb, 0x14, 0xfffffff0);
	ret |= sisusb_read_pci_config(sisusb, 0x14, &tmp32);
	tmp32 &= 0x0f;
	tmp32 |= SISUSB_PCI_MMIOBASE;
	ret |= sisusb_write_pci_config(sisusb, 0x14, tmp32);

	/* Init BAR 2 (i/o ports) */
	ret |= sisusb_read_pci_config(sisusb, 0x18, &tmp32);
	ret |= sisusb_write_pci_config(sisusb, 0x18, 0xfffffff0);
	ret |= sisusb_read_pci_config(sisusb, 0x18, &tmp32);
	tmp32 &= 0x0f;
	tmp32 |= SISUSB_PCI_IOPORTBASE;
	ret |= sisusb_write_pci_config(sisusb, 0x18, tmp32);

	/* Enable memory and i/o access */
	ret |= sisusb_read_pci_config(sisusb, 0x04, &tmp32);
	tmp32 |= 0x3;
	ret |= sisusb_write_pci_config(sisusb, 0x04, tmp32);

	if (ret == 0) {
		/* Some further magic */
		packet.header  = 0x001f;
		packet.address = 0x00000050;
		packet.data    = 0x000000ff;
		ret |= sisusb_send_bridge_packet(sisusb, 10, &packet, 0);
	}

	return ret;
}