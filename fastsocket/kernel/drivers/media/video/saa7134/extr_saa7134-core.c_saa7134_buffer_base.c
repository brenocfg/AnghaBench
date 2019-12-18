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
struct videobuf_dmabuf {TYPE_1__* sglist; } ;
struct saa7134_buf {int /*<<< orphan*/  vb; } ;
struct TYPE_2__ {scalar_t__ offset; } ;

/* Variables and functions */
 int saa7134_buffer_startpage (struct saa7134_buf*) ; 
 struct videobuf_dmabuf* videobuf_to_dma (int /*<<< orphan*/ *) ; 

unsigned long saa7134_buffer_base(struct saa7134_buf *buf)
{
	unsigned long base;
	struct videobuf_dmabuf *dma=videobuf_to_dma(&buf->vb);

	base  = saa7134_buffer_startpage(buf) * 4096;
	base += dma->sglist[0].offset;
	return base;
}