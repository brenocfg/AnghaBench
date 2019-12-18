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
typedef  int /*<<< orphan*/  u32 ;
struct pci_dev {int dummy; } ;
struct lanai_buffer {int dmaaddr; int /*<<< orphan*/ * start; int /*<<< orphan*/ * end; int /*<<< orphan*/ * ptr; } ;

/* Variables and functions */
 int /*<<< orphan*/  APRINTK (int,char*,unsigned long) ; 
 size_t LANAI_PAGE_SIZE ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * pci_alloc_consistent (struct pci_dev*,int,int*) ; 

__attribute__((used)) static void lanai_buf_allocate(struct lanai_buffer *buf,
	size_t bytes, size_t minbytes, struct pci_dev *pci)
{
	int size;

	if (bytes > (128 * 1024))	/* max lanai buffer size */
		bytes = 128 * 1024;
	for (size = LANAI_PAGE_SIZE; size < bytes; size *= 2)
		;
	if (minbytes < LANAI_PAGE_SIZE)
		minbytes = LANAI_PAGE_SIZE;
	do {
		/*
		 * Technically we could use non-consistent mappings for
		 * everything, but the way the lanai uses DMA memory would
		 * make that a terrific pain.  This is much simpler.
		 */
		buf->start = pci_alloc_consistent(pci, size, &buf->dmaaddr);
		if (buf->start != NULL) {	/* Success */
			/* Lanai requires 256-byte alignment of DMA bufs */
			APRINTK((buf->dmaaddr & ~0xFFFFFF00) == 0,
			    "bad dmaaddr: 0x%lx\n",
			    (unsigned long) buf->dmaaddr);
			buf->ptr = buf->start;
			buf->end = (u32 *)
			    (&((unsigned char *) buf->start)[size]);
			memset(buf->start, 0, size);
			break;
		}
		size /= 2;
	} while (size >= minbytes);
}