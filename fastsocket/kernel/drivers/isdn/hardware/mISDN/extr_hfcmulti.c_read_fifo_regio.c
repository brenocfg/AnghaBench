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
typedef  int /*<<< orphan*/  u_char ;
typedef  int /*<<< orphan*/  u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct hfc_multi {scalar_t__ pci_iobase; } ;

/* Variables and functions */
 int /*<<< orphan*/  A_FIFO_DATA0 ; 
 int /*<<< orphan*/  inb (scalar_t__) ; 
 int /*<<< orphan*/  inl (scalar_t__) ; 
 int /*<<< orphan*/  inw (scalar_t__) ; 
 int /*<<< orphan*/  le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  outb (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void
read_fifo_regio(struct hfc_multi *hc, u_char *data, int len)
{
	outb(A_FIFO_DATA0, (hc->pci_iobase)+4);
	while (len>>2) {
		*(u32 *)data = le32_to_cpu(inl(hc->pci_iobase));
		data += 4;
		len -= 4;
	}
	while (len>>1) {
		*(u16 *)data = le16_to_cpu(inw(hc->pci_iobase));
		data += 2;
		len -= 2;
	}
	while (len) {
		*data = inb(hc->pci_iobase);
		data++;
		len--;
	}
}