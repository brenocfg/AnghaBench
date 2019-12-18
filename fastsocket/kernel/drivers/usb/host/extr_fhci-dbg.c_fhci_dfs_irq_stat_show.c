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
struct seq_file {struct fhci_hcd* private; } ;
struct fhci_hcd {int* usb_irq_stat; } ;

/* Variables and functions */
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,int,int,int,int,int,int,int,int,int,int,int,int,int) ; 

__attribute__((used)) static int fhci_dfs_irq_stat_show(struct seq_file *s, void *v)
{
	struct fhci_hcd *fhci = s->private;
	int *usb_irq_stat = fhci->usb_irq_stat;

	seq_printf(s,
		"RXB: %d\n" "TXB: %d\n" "BSY: %d\n"
		"SOF: %d\n" "TXE0: %d\n" "TXE1: %d\n"
		"TXE2: %d\n" "TXE3: %d\n" "IDLE: %d\n"
		"RESET: %d\n" "SFT: %d\n" "MSF: %d\n"
		"IDLE_ONLY: %d\n",
		usb_irq_stat[0], usb_irq_stat[1], usb_irq_stat[2],
		usb_irq_stat[3], usb_irq_stat[4], usb_irq_stat[5],
		usb_irq_stat[6], usb_irq_stat[7], usb_irq_stat[8],
		usb_irq_stat[9], usb_irq_stat[10], usb_irq_stat[11],
		usb_irq_stat[12]);

	return 0;
}