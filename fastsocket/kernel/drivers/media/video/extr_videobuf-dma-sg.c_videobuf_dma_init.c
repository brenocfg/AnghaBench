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
struct videobuf_dmabuf {int /*<<< orphan*/  magic; } ;

/* Variables and functions */
 int /*<<< orphan*/  MAGIC_DMABUF ; 
 int /*<<< orphan*/  memset (struct videobuf_dmabuf*,int /*<<< orphan*/ ,int) ; 

void videobuf_dma_init(struct videobuf_dmabuf *dma)
{
	memset(dma, 0, sizeof(*dma));
	dma->magic = MAGIC_DMABUF;
}