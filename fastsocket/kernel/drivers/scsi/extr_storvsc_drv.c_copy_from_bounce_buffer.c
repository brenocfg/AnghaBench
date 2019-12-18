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
struct scatterlist {unsigned long offset; unsigned int length; } ;

/* Variables and functions */
 int /*<<< orphan*/  local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  local_irq_save (unsigned long) ; 
 int /*<<< orphan*/  memcpy (void*,void*,unsigned int) ; 
 unsigned int min (unsigned int,unsigned int) ; 
 unsigned long sg_kmap_atomic (struct scatterlist*,int) ; 
 int /*<<< orphan*/  sg_kunmap_atomic (unsigned long) ; 

__attribute__((used)) static unsigned int copy_from_bounce_buffer(struct scatterlist *orig_sgl,
					    struct scatterlist *bounce_sgl,
					    unsigned int orig_sgl_count,
					    unsigned int bounce_sgl_count)
{
	int i;
	int j = 0;
	unsigned long src, dest;
	unsigned int srclen, destlen, copylen;
	unsigned int total_copied = 0;
	unsigned long bounce_addr = 0;
	unsigned long dest_addr = 0;
	unsigned long flags;

	local_irq_save(flags);

	for (i = 0; i < orig_sgl_count; i++) {
		dest_addr = sg_kmap_atomic(orig_sgl,i) + orig_sgl[i].offset;
		dest = dest_addr;
		destlen = orig_sgl[i].length;

		if (bounce_addr == 0)
			bounce_addr = sg_kmap_atomic(bounce_sgl,j);

		while (destlen) {
			src = bounce_addr + bounce_sgl[j].offset;
			srclen = bounce_sgl[j].length - bounce_sgl[j].offset;

			copylen = min(srclen, destlen);
			memcpy((void *)dest, (void *)src, copylen);

			total_copied += copylen;
			bounce_sgl[j].offset += copylen;
			destlen -= copylen;
			dest += copylen;

			if (bounce_sgl[j].offset == bounce_sgl[j].length) {
				/* full */
				sg_kunmap_atomic(bounce_addr);
				j++;

				/*
				 * It is possible that the number of elements
				 * in the bounce buffer may not be equal to
				 * the number of elements in the original
				 * scatter list. Handle this correctly.
				 */

				if (j == bounce_sgl_count) {
					/*
					 * We are done; cleanup and return.
					 */
					sg_kunmap_atomic(dest_addr - orig_sgl[i].offset);
					local_irq_restore(flags);
					return total_copied;
				}

				/* if we need to use another bounce buffer */
				if (destlen || i != orig_sgl_count - 1)
					bounce_addr = sg_kmap_atomic(bounce_sgl,j);
			} else if (destlen == 0 && i == orig_sgl_count - 1) {
				/* unmap the last bounce that is < PAGE_SIZE */
				sg_kunmap_atomic(bounce_addr);
			}
		}

		sg_kunmap_atomic(dest_addr - orig_sgl[i].offset);
	}

	local_irq_restore(flags);

	return total_copied;
}