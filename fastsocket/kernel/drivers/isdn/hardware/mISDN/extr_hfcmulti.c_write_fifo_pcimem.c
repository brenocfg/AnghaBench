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
 int /*<<< orphan*/  cpu_to_le16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writeb (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  writew (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void
write_fifo_pcimem(struct hfc_multi *hc, u_char *data, int len)
{
	while (len>>2) {
		writel(cpu_to_le32(*(u32 *)data),
			hc->pci_membase + A_FIFO_DATA0);
		data += 4;
		len -= 4;
	}
	while (len>>1) {
		writew(cpu_to_le16(*(u16 *)data),
			hc->pci_membase + A_FIFO_DATA0);
		data += 2;
		len -= 2;
	}
	while (len) {
		writeb(*data, hc->pci_membase + A_FIFO_DATA0);
		data++;
		len--;
	}
}