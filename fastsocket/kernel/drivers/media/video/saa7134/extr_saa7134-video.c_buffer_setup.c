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
struct videobuf_queue {struct saa7134_fh* priv_data; } ;
struct saa7134_fh {int width; int height; TYPE_1__* fmt; } ;
struct TYPE_2__ {int depth; } ;

/* Variables and functions */
 unsigned int gbuffers ; 
 unsigned int saa7134_buffer_count (unsigned int,unsigned int) ; 

__attribute__((used)) static int
buffer_setup(struct videobuf_queue *q, unsigned int *count, unsigned int *size)
{
	struct saa7134_fh *fh = q->priv_data;

	*size = fh->fmt->depth * fh->width * fh->height >> 3;
	if (0 == *count)
		*count = gbuffers;
	*count = saa7134_buffer_count(*size,*count);
	return 0;
}