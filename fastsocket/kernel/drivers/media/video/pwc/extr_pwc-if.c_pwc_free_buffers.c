#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct pwc_device {int len_per_image; int /*<<< orphan*/ * image_data; TYPE_2__* decompress_data; TYPE_2__* fbuf; TYPE_1__* sbuf; } ;
struct TYPE_4__ {int /*<<< orphan*/ * data; } ;
struct TYPE_3__ {TYPE_2__* data; } ;

/* Variables and functions */
 int MAX_ISO_BUFS ; 
 int /*<<< orphan*/  PWC_DEBUG_MEMORY (char*,...) ; 
 int default_fbufs ; 
 int /*<<< orphan*/  kfree (TYPE_2__*) ; 
 int pwc_mbufs ; 
 int /*<<< orphan*/  pwc_rvfree (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  vfree (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void pwc_free_buffers(struct pwc_device *pdev)
{
	int i;

	PWC_DEBUG_MEMORY("Entering free_buffers(%p).\n", pdev);

	if (pdev == NULL)
		return;
	/* Release Iso-pipe buffers */
	for (i = 0; i < MAX_ISO_BUFS; i++)
		if (pdev->sbuf[i].data != NULL) {
			PWC_DEBUG_MEMORY("Freeing ISO buffer at %p.\n", pdev->sbuf[i].data);
			kfree(pdev->sbuf[i].data);
			pdev->sbuf[i].data = NULL;
		}

	/* The same for frame buffers */
	if (pdev->fbuf != NULL) {
		for (i = 0; i < default_fbufs; i++) {
			if (pdev->fbuf[i].data != NULL) {
				PWC_DEBUG_MEMORY("Freeing frame buffer %d at %p.\n", i, pdev->fbuf[i].data);
				vfree(pdev->fbuf[i].data);
				pdev->fbuf[i].data = NULL;
			}
		}
		kfree(pdev->fbuf);
		pdev->fbuf = NULL;
	}

	/* Intermediate decompression buffer & tables */
	if (pdev->decompress_data != NULL) {
		PWC_DEBUG_MEMORY("Freeing decompression buffer at %p.\n", pdev->decompress_data);
		kfree(pdev->decompress_data);
		pdev->decompress_data = NULL;
	}

	/* Release image buffers */
	if (pdev->image_data != NULL) {
		PWC_DEBUG_MEMORY("Freeing image buffer at %p.\n", pdev->image_data);
		pwc_rvfree(pdev->image_data, pwc_mbufs * pdev->len_per_image);
	}
	pdev->image_data = NULL;

	PWC_DEBUG_MEMORY("Leaving free_buffers().\n");
}