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
struct pci_dev {int dummy; } ;
struct btcx_riscmem {int dma; int /*<<< orphan*/ * cpu; } ;
typedef  int /*<<< orphan*/  __le32 ;

/* Variables and functions */
 int RISC_IRQ1 ; 
 int RISC_JUMP ; 
 int RISC_WRITECR ; 
 int btcx_riscmem_alloc (struct pci_dev*,struct btcx_riscmem*,int) ; 
 void* cpu_to_le32 (int) ; 

int cx25821_risc_stopper(struct pci_dev *pci, struct btcx_riscmem *risc,
			 u32 reg, u32 mask, u32 value)
{
	__le32 *rp;
	int rc;

	rc = btcx_riscmem_alloc(pci, risc, 4 * 16);

	if (rc < 0)
		return rc;

	/* write risc instructions */
	rp = risc->cpu;

	*(rp++) = cpu_to_le32(RISC_WRITECR | RISC_IRQ1);
	*(rp++) = cpu_to_le32(reg);
	*(rp++) = cpu_to_le32(value);
	*(rp++) = cpu_to_le32(mask);
	*(rp++) = cpu_to_le32(RISC_JUMP);
	*(rp++) = cpu_to_le32(risc->dma);
	*(rp++) = cpu_to_le32(0);	/* bits 63-32 */
	return 0;
}