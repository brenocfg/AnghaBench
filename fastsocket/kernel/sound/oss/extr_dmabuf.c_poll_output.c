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
struct file {int dummy; } ;
struct dma_buffparms {int mapping_flags; scalar_t__ dma_mode; scalar_t__ qlen; } ;
struct audio_operations {int open_mode; struct dma_buffparms* dmap_out; } ;
typedef  int /*<<< orphan*/  poll_table ;

/* Variables and functions */
 int DMA_MAP_MAPPED ; 
 int /*<<< orphan*/  DMAbuf_space_in_queue (int) ; 
 scalar_t__ DMODE_INPUT ; 
 scalar_t__ DMODE_NONE ; 
 int OPEN_WRITE ; 
 unsigned int POLLOUT ; 
 unsigned int POLLWRNORM ; 
 struct audio_operations** audio_devs ; 

__attribute__((used)) static unsigned int poll_output(struct file * file, int dev, poll_table *wait)
{
	struct audio_operations *adev = audio_devs[dev];
	struct dma_buffparms *dmap = adev->dmap_out;
	
	if (!(adev->open_mode & OPEN_WRITE))
		return 0;
	if (dmap->mapping_flags & DMA_MAP_MAPPED) {
		if (dmap->qlen)
			return POLLOUT | POLLWRNORM;
		return 0;
	}
	if (dmap->dma_mode == DMODE_INPUT)
		return 0;
	if (dmap->dma_mode == DMODE_NONE)
		return POLLOUT | POLLWRNORM;
	if (!DMAbuf_space_in_queue(dev))
		return 0;
	return POLLOUT | POLLWRNORM;
}