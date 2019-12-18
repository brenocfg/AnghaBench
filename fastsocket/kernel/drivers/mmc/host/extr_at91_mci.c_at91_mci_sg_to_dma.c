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
struct scatterlist {int offset; int /*<<< orphan*/  length; } ;
struct mmc_data {unsigned int blksz; unsigned int blocks; unsigned int sg_len; struct scatterlist* sg; } ;
struct at91mci_host {unsigned int* buffer; int total_length; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  KM_BIO_SRC_IRQ ; 
 scalar_t__ cpu_is_at91rm9200 () ; 
 scalar_t__ cpu_is_at91sam9260 () ; 
 scalar_t__ cpu_is_at91sam9263 () ; 
 unsigned int* kmap_atomic (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kunmap_atomic (unsigned int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (unsigned int*,unsigned int*,int) ; 
 int /*<<< orphan*/  memset (unsigned int*,int /*<<< orphan*/ ,int) ; 
 int min (unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sg_page (struct scatterlist*) ; 
 int /*<<< orphan*/  swab32 (unsigned int) ; 

__attribute__((used)) static inline void at91_mci_sg_to_dma(struct at91mci_host *host, struct mmc_data *data)
{
	unsigned int len, i, size;
	unsigned *dmabuf = host->buffer;

	size = data->blksz * data->blocks;
	len = data->sg_len;

	/* AT91SAM926[0/3] Data Write Operation and number of bytes erratum */
	if (cpu_is_at91sam9260() || cpu_is_at91sam9263())
		if (host->total_length == 12)
			memset(dmabuf, 0, 12);

	/*
	 * Just loop through all entries. Size might not
	 * be the entire list though so make sure that
	 * we do not transfer too much.
	 */
	for (i = 0; i < len; i++) {
		struct scatterlist *sg;
		int amount;
		unsigned int *sgbuffer;

		sg = &data->sg[i];

		sgbuffer = kmap_atomic(sg_page(sg), KM_BIO_SRC_IRQ) + sg->offset;
		amount = min(size, sg->length);
		size -= amount;

		if (cpu_is_at91rm9200()) {	/* AT91RM9200 errata */
			int index;

			for (index = 0; index < (amount / 4); index++)
				*dmabuf++ = swab32(sgbuffer[index]);
		} else {
			memcpy(dmabuf, sgbuffer, amount);
			dmabuf += amount;
		}

		kunmap_atomic(sgbuffer, KM_BIO_SRC_IRQ);

		if (size == 0)
			break;
	}

	/*
	 * Check that we didn't get a request to transfer
	 * more data than can fit into the SG list.
	 */
	BUG_ON(size != 0);
}