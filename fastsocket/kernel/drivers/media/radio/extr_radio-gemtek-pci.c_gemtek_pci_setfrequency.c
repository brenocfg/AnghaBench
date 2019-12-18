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
struct gemtek_pci {int iobase; unsigned long current_frequency; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  gemtek_pci_cmd (int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gemtek_pci_nil (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gemtek_pci_out (int,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  outw (int,int) ; 

__attribute__((used)) static void gemtek_pci_setfrequency(struct gemtek_pci *card, unsigned long frequency)
{
	int i;
	u32 value = frequency / 200 + 856;
	u16 mask = 0x8000;
	u8 last_byte;
	u32 port = card->iobase;

	mutex_lock(&card->lock);
	card->current_frequency = frequency;
	last_byte = gemtek_pci_out(0x06, port);

	i = 0;
	do {
		gemtek_pci_nil(port, &last_byte);
		i++;
	} while (i < 9);

	i = 0;
	do {
		gemtek_pci_cmd(value & mask, port, &last_byte);
		mask >>= 1;
		i++;
	} while (i < 16);

	outw(0x10, port);
	mutex_unlock(&card->lock);
}