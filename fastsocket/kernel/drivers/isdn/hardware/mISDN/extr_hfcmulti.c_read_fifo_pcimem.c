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
struct hfc_multi {scalar_t__ pci_membase; } ;

/* Variables and functions */
 scalar_t__ A_FIFO_DATA0 ; 
 int /*<<< orphan*/  le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  readb (scalar_t__) ; 
 int /*<<< orphan*/  readl (scalar_t__) ; 
 int /*<<< orphan*/  readw (scalar_t__) ; 

__attribute__((used)) static void
read_fifo_pcimem(struct hfc_multi *hc, u_char *data, int len)
{
	while (len>>2) {
		*(u32 *)data =
			le32_to_cpu(readl(hc->pci_membase + A_FIFO_DATA0));
		data += 4;
		len -= 4;
	}
	while (len>>1) {
		*(u16 *)data =
			le16_to_cpu(readw(hc->pci_membase + A_FIFO_DATA0));
		data += 2;
		len -= 2;
	}
	while (len) {
		*data = readb(hc->pci_membase + A_FIFO_DATA0);
		data++;
		len--;
	}
}