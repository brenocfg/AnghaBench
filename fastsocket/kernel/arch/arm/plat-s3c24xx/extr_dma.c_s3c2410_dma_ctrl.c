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
struct s3c2410_dma_chan {int dummy; } ;
typedef  enum s3c2410_chan_op { ____Placeholder_s3c2410_chan_op } s3c2410_chan_op ;

/* Variables and functions */
 int EINVAL ; 
 int ENOENT ; 
#define  S3C2410_DMAOP_FLUSH 134 
#define  S3C2410_DMAOP_PAUSE 133 
#define  S3C2410_DMAOP_RESUME 132 
#define  S3C2410_DMAOP_START 131 
#define  S3C2410_DMAOP_STARTED 130 
#define  S3C2410_DMAOP_STOP 129 
#define  S3C2410_DMAOP_TIMEOUT 128 
 int s3c2410_dma_dostop (struct s3c2410_dma_chan*) ; 
 int s3c2410_dma_flush (struct s3c2410_dma_chan*) ; 
 int s3c2410_dma_start (struct s3c2410_dma_chan*) ; 
 int s3c2410_dma_started (struct s3c2410_dma_chan*) ; 
 struct s3c2410_dma_chan* s3c_dma_lookup_channel (unsigned int) ; 

int
s3c2410_dma_ctrl(unsigned int channel, enum s3c2410_chan_op op)
{
	struct s3c2410_dma_chan *chan = s3c_dma_lookup_channel(channel);

	if (chan == NULL)
		return -EINVAL;

	switch (op) {
	case S3C2410_DMAOP_START:
		return s3c2410_dma_start(chan);

	case S3C2410_DMAOP_STOP:
		return s3c2410_dma_dostop(chan);

	case S3C2410_DMAOP_PAUSE:
	case S3C2410_DMAOP_RESUME:
		return -ENOENT;

	case S3C2410_DMAOP_FLUSH:
		return s3c2410_dma_flush(chan);

	case S3C2410_DMAOP_STARTED:
		return s3c2410_dma_started(chan);

	case S3C2410_DMAOP_TIMEOUT:
		return 0;

	}

	return -ENOENT;      /* unknown, don't bother */
}