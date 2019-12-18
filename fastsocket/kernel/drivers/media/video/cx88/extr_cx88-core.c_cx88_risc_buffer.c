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
struct scatterlist {int dummy; } ;
struct pci_dev {int dummy; } ;
struct btcx_riscmem {int size; int /*<<< orphan*/ * cpu; int /*<<< orphan*/ * jmp; } ;
typedef  int /*<<< orphan*/  __le32 ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 unsigned int PAGE_SIZE ; 
 unsigned int UNSET ; 
 int btcx_riscmem_alloc (struct pci_dev*,struct btcx_riscmem*,int) ; 
 int /*<<< orphan*/ * cx88_risc_field (int /*<<< orphan*/ *,struct scatterlist*,unsigned int,int,unsigned int,unsigned int,unsigned int,int /*<<< orphan*/ ) ; 

int cx88_risc_buffer(struct pci_dev *pci, struct btcx_riscmem *risc,
		     struct scatterlist *sglist,
		     unsigned int top_offset, unsigned int bottom_offset,
		     unsigned int bpl, unsigned int padding, unsigned int lines)
{
	u32 instructions,fields;
	__le32 *rp;
	int rc;

	fields = 0;
	if (UNSET != top_offset)
		fields++;
	if (UNSET != bottom_offset)
		fields++;

	/* estimate risc mem: worst case is one write per page border +
	   one write per scan line + syncs + jump (all 2 dwords).  Padding
	   can cause next bpl to start close to a page border.  First DMA
	   region may be smaller than PAGE_SIZE */
	instructions  = fields * (1 + ((bpl + padding) * lines) / PAGE_SIZE + lines);
	instructions += 2;
	if ((rc = btcx_riscmem_alloc(pci,risc,instructions*8)) < 0)
		return rc;

	/* write risc instructions */
	rp = risc->cpu;
	if (UNSET != top_offset)
		rp = cx88_risc_field(rp, sglist, top_offset, 0,
				     bpl, padding, lines, 0);
	if (UNSET != bottom_offset)
		rp = cx88_risc_field(rp, sglist, bottom_offset, 0x200,
				     bpl, padding, lines, 0);

	/* save pointer to jmp instruction address */
	risc->jmp = rp;
	BUG_ON((risc->jmp - risc->cpu + 2) * sizeof (*risc->cpu) > risc->size);
	return 0;
}