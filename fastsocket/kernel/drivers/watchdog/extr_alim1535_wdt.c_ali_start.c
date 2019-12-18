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

/* Variables and functions */
 int /*<<< orphan*/  ali_lock ; 
 int /*<<< orphan*/  ali_pci ; 
 int ali_timeout_bits ; 
 int /*<<< orphan*/  pci_read_config_dword (int /*<<< orphan*/ ,int,int*) ; 
 int /*<<< orphan*/  pci_write_config_dword (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ali_start(void)
{
	u32 val;

	spin_lock(&ali_lock);

	pci_read_config_dword(ali_pci, 0xCC, &val);
	val &= ~0x3F;	/* Mask count */
	val |= (1 << 25) | ali_timeout_bits;
	pci_write_config_dword(ali_pci, 0xCC, val);

	spin_unlock(&ali_lock);
}