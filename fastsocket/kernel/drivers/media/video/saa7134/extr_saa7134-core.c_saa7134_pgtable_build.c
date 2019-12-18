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
struct scatterlist {unsigned int length; scalar_t__ offset; } ;
struct saa7134_pgtable {int /*<<< orphan*/ * cpu; } ;
struct pci_dev {int dummy; } ;
typedef  int /*<<< orphan*/  __le32 ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  cpu_to_le32 (scalar_t__) ; 
 scalar_t__ sg_dma_address (struct scatterlist*) ; 

int saa7134_pgtable_build(struct pci_dev *pci, struct saa7134_pgtable *pt,
			  struct scatterlist *list, unsigned int length,
			  unsigned int startpage)
{
	__le32        *ptr;
	unsigned int  i,p;

	BUG_ON(NULL == pt || NULL == pt->cpu);

	ptr = pt->cpu + startpage;
	for (i = 0; i < length; i++, list++)
		for (p = 0; p * 4096 < list->length; p++, ptr++)
			*ptr = cpu_to_le32(sg_dma_address(list) - list->offset);
	return 0;
}