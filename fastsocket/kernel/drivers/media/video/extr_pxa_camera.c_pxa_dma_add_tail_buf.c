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
struct pxa_dma_desc {int /*<<< orphan*/  ddadr; } ;
struct pxa_camera_dev {int channels; struct pxa_dma_desc** sg_tail; } ;
struct pxa_buffer {TYPE_1__* dmas; } ;
struct TYPE_2__ {int sglen; int /*<<< orphan*/  sg_dma; struct pxa_dma_desc* sg_cpu; } ;

/* Variables and functions */
 int /*<<< orphan*/  DDADR_STOP ; 

__attribute__((used)) static void pxa_dma_add_tail_buf(struct pxa_camera_dev *pcdev,
				 struct pxa_buffer *buf)
{
	int i;
	struct pxa_dma_desc *buf_last_desc;

	for (i = 0; i < pcdev->channels; i++) {
		buf_last_desc = buf->dmas[i].sg_cpu + buf->dmas[i].sglen;
		buf_last_desc->ddadr = DDADR_STOP;

		if (pcdev->sg_tail[i])
			/* Link the new buffer to the old tail */
			pcdev->sg_tail[i]->ddadr = buf->dmas[i].sg_dma;

		/* Update the channel tail */
		pcdev->sg_tail[i] = buf_last_desc;
	}
}