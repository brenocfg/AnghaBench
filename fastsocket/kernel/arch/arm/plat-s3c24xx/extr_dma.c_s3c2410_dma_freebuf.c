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
struct s3c2410_dma_buf {int magic; } ;

/* Variables and functions */
 int BUF_MAGIC ; 
 int /*<<< orphan*/  dma_kmem ; 
 int /*<<< orphan*/  kmem_cache_free (int /*<<< orphan*/ ,struct s3c2410_dma_buf*) ; 
 int /*<<< orphan*/  printk (char*,struct s3c2410_dma_buf*) ; 

__attribute__((used)) static inline void
s3c2410_dma_freebuf(struct s3c2410_dma_buf *buf)
{
	int magicok = (buf->magic == BUF_MAGIC);

	buf->magic = -1;

	if (magicok) {
		kmem_cache_free(dma_kmem, buf);
	} else {
		printk("s3c2410_dma_freebuf: buff %p with bad magic\n", buf);
	}
}