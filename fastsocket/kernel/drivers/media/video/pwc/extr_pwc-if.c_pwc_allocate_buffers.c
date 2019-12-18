#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct pwc_frame_buf {int dummy; } ;
struct pwc_device {int len_per_image; TYPE_3__* images; void* image_data; int /*<<< orphan*/  type; TYPE_2__* fbuf; TYPE_1__* sbuf; } ;
struct TYPE_6__ {int offset; scalar_t__ vma_use_count; } ;
struct TYPE_5__ {int /*<<< orphan*/ * data; } ;
struct TYPE_4__ {int /*<<< orphan*/ * data; } ;

/* Variables and functions */
 scalar_t__ DEVICE_USE_CODEC1 (int /*<<< orphan*/ ) ; 
 int ENOMEM ; 
 int ENXIO ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int ISO_BUFFER_SIZE ; 
 int MAX_IMAGES ; 
 int MAX_ISO_BUFS ; 
 int /*<<< orphan*/  PWC_DEBUG_MEMORY (char*,...) ; 
 int /*<<< orphan*/  PWC_ERROR (char*,...) ; 
 int /*<<< orphan*/  PWC_FRAME_SIZE ; 
 int default_fbufs ; 
 void* kzalloc (int,int /*<<< orphan*/ ) ; 
 int pwc_dec1_alloc (struct pwc_device*) ; 
 int pwc_dec23_alloc (struct pwc_device*) ; 
 int pwc_mbufs ; 
 void* pwc_rvmalloc (int) ; 
 void* vzalloc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int pwc_allocate_buffers(struct pwc_device *pdev)
{
	int i, err;
	void *kbuf;

	PWC_DEBUG_MEMORY(">> pwc_allocate_buffers(pdev = 0x%p)\n", pdev);

	if (pdev == NULL)
		return -ENXIO;

	/* Allocate Isochronuous pipe buffers */
	for (i = 0; i < MAX_ISO_BUFS; i++) {
		if (pdev->sbuf[i].data == NULL) {
			kbuf = kzalloc(ISO_BUFFER_SIZE, GFP_KERNEL);
			if (kbuf == NULL) {
				PWC_ERROR("Failed to allocate iso buffer %d.\n", i);
				return -ENOMEM;
			}
			PWC_DEBUG_MEMORY("Allocated iso buffer at %p.\n", kbuf);
			pdev->sbuf[i].data = kbuf;
		}
	}

	/* Allocate frame buffer structure */
	if (pdev->fbuf == NULL) {
		kbuf = kzalloc(default_fbufs * sizeof(struct pwc_frame_buf), GFP_KERNEL);
		if (kbuf == NULL) {
			PWC_ERROR("Failed to allocate frame buffer structure.\n");
			return -ENOMEM;
		}
		PWC_DEBUG_MEMORY("Allocated frame buffer structure at %p.\n", kbuf);
		pdev->fbuf = kbuf;
	}

	/* create frame buffers, and make circular ring */
	for (i = 0; i < default_fbufs; i++) {
		if (pdev->fbuf[i].data == NULL) {
			kbuf = vzalloc(PWC_FRAME_SIZE); /* need vmalloc since frame buffer > 128K */
			if (kbuf == NULL) {
				PWC_ERROR("Failed to allocate frame buffer %d.\n", i);
				return -ENOMEM;
			}
			PWC_DEBUG_MEMORY("Allocated frame buffer %d at %p.\n", i, kbuf);
			pdev->fbuf[i].data = kbuf;
		}
	}

	/* Allocate decompressor table space */
	if (DEVICE_USE_CODEC1(pdev->type))
		err = pwc_dec1_alloc(pdev);
	else
		err = pwc_dec23_alloc(pdev);

	if (err) {
		PWC_ERROR("Failed to allocate decompress table.\n");
		return err;
	}

	/* Allocate image buffer; double buffer for mmap() */
	kbuf = pwc_rvmalloc(pwc_mbufs * pdev->len_per_image);
	if (kbuf == NULL) {
		PWC_ERROR("Failed to allocate image buffer(s). needed (%d)\n",
				pwc_mbufs * pdev->len_per_image);
		return -ENOMEM;
	}
	PWC_DEBUG_MEMORY("Allocated image buffer at %p.\n", kbuf);
	pdev->image_data = kbuf;
	for (i = 0; i < pwc_mbufs; i++) {
		pdev->images[i].offset = i * pdev->len_per_image;
		pdev->images[i].vma_use_count = 0;
	}
	for (; i < MAX_IMAGES; i++) {
		pdev->images[i].offset = 0;
	}

	kbuf = NULL;

	PWC_DEBUG_MEMORY("<< pwc_allocate_buffers()\n");
	return 0;
}