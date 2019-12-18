#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {unsigned long* virtual; unsigned int page_count; scalar_t__* dma_cpu; int /*<<< orphan*/  dma; } ;
struct vino_framebuffer {unsigned int size; TYPE_1__ desc_table; int /*<<< orphan*/  data_format; } ;
typedef  scalar_t__ dma_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_FROM_DEVICE ; 
 int EINVAL ; 
 int ENOBUFS ; 
 int ENOMEM ; 
 int GFP_DMA ; 
 int GFP_KERNEL ; 
 unsigned int PAGE_SIZE ; 
 int /*<<< orphan*/  SetPageReserved (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VINO_DATA_FMT_NONE ; 
 scalar_t__ VINO_DESC_STOP ; 
 unsigned int VINO_PAGE_RATIO ; 
 unsigned int VINO_PAGE_SIZE ; 
 scalar_t__* dma_alloc_coherent (int /*<<< orphan*/ *,unsigned int,int /*<<< orphan*/ *,int) ; 
 scalar_t__ dma_map_single (int /*<<< orphan*/ *,void*,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dprintk (char*,...) ; 
 unsigned long get_zeroed_page (int) ; 
 int /*<<< orphan*/  kfree (unsigned long*) ; 
 scalar_t__ kmalloc (unsigned int,int) ; 
 int /*<<< orphan*/  memset (struct vino_framebuffer*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  vino_free_buffer_with_count (struct vino_framebuffer*,unsigned int) ; 
 int /*<<< orphan*/  virt_to_page (void*) ; 

__attribute__((used)) static int vino_allocate_buffer(struct vino_framebuffer *fb,
				unsigned int size)
{
	unsigned int count, i, j;
	int ret = 0;

	dprintk("vino_allocate_buffer():\n");

	if (size < 1)
		return -EINVAL;

	memset(fb, 0, sizeof(struct vino_framebuffer));

	count = ((size / PAGE_SIZE) + 4) & ~3;

	dprintk("vino_allocate_buffer(): size = %d, count = %d\n",
		size, count);

	/* allocate memory for table with virtual (page) addresses */
	fb->desc_table.virtual = (unsigned long *)
		kmalloc(count * sizeof(unsigned long), GFP_KERNEL);
	if (!fb->desc_table.virtual)
		return -ENOMEM;

	/* allocate memory for table with dma addresses
	 * (has space for four extra descriptors) */
	fb->desc_table.dma_cpu =
		dma_alloc_coherent(NULL, VINO_PAGE_RATIO * (count + 4) *
				   sizeof(dma_addr_t), &fb->desc_table.dma,
				   GFP_KERNEL | GFP_DMA);
	if (!fb->desc_table.dma_cpu) {
		ret = -ENOMEM;
		goto out_free_virtual;
	}

	/* allocate pages for the buffer and acquire the according
	 * dma addresses */
	for (i = 0; i < count; i++) {
		dma_addr_t dma_data_addr;

		fb->desc_table.virtual[i] =
			get_zeroed_page(GFP_KERNEL | GFP_DMA);
		if (!fb->desc_table.virtual[i]) {
			ret = -ENOBUFS;
			break;
		}

		dma_data_addr =
			dma_map_single(NULL,
				       (void *)fb->desc_table.virtual[i],
				       PAGE_SIZE, DMA_FROM_DEVICE);

		for (j = 0; j < VINO_PAGE_RATIO; j++) {
			fb->desc_table.dma_cpu[VINO_PAGE_RATIO * i + j] =
				dma_data_addr + VINO_PAGE_SIZE * j;
		}

		SetPageReserved(virt_to_page((void *)fb->desc_table.virtual[i]));
	}

	/* page_count needs to be set anyway, because the descriptor table has
	 * been allocated according to this number */
	fb->desc_table.page_count = count;

	if (ret) {
		/* the descriptor with index i doesn't contain
		 * a valid address yet */
		vino_free_buffer_with_count(fb, i);
		return ret;
	}

	//fb->size = size;
	fb->size = count * PAGE_SIZE;
	fb->data_format = VINO_DATA_FMT_NONE;

	/* set the dma stop-bit for the last (count+1)th descriptor */
	fb->desc_table.dma_cpu[VINO_PAGE_RATIO * count] = VINO_DESC_STOP;
	return 0;

 out_free_virtual:
	kfree(fb->desc_table.virtual);
	return ret;
}