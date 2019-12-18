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
struct s3c2410_dma_chan {scalar_t__ load_state; } ;

/* Variables and functions */
 scalar_t__ S3C2410_DMALOAD_1RUNNING ; 
 scalar_t__ S3C2410_DMALOAD_NONE ; 

__attribute__((used)) static int
s3c2410_dma_canload(struct s3c2410_dma_chan *chan)
{
	if (chan->load_state == S3C2410_DMALOAD_NONE ||
	    chan->load_state == S3C2410_DMALOAD_1RUNNING)
		return 1;

	return 0;
}