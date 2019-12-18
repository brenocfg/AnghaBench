#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  off_t ;
struct TYPE_8__ {char* name; } ;
struct TYPE_7__ {int /*<<< orphan*/  lock; TYPE_1__* controller; } ;
struct TYPE_6__ {int flags; size_t devType; char* fileName; int lineNum; size_t lastDevType; } ;
struct TYPE_5__ {TYPE_2__* channel; } ;
typedef  TYPE_2__ DMA_Channel_t ;

/* Variables and functions */
 int DMA_CHANNEL_FLAG_IN_USE ; 
 int DMA_CHANNEL_FLAG_IS_DEDICATED ; 
 int DMA_CHANNEL_FLAG_LARGE_FIFO ; 
 int DMA_CHANNEL_FLAG_NO_ISR ; 
 size_t DMA_DEVICE_NONE ; 
 int DMA_NUM_CHANNELS ; 
 int DMA_NUM_CONTROLLERS ; 
 TYPE_4__* DMA_gDeviceAttribute ; 
 int ERESTARTSYS ; 
 scalar_t__ down_interruptible (int /*<<< orphan*/ *) ; 
 TYPE_3__ gDMA ; 
 scalar_t__ sprintf (char*,char*,...) ; 
 int /*<<< orphan*/  up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int dma_proc_read_channels(char *buf, char **start, off_t offset,
				  int count, int *eof, void *data)
{
	int controllerIdx;
	int channelIdx;
	int limit = count - 200;
	int len = 0;
	DMA_Channel_t *channel;

	if (down_interruptible(&gDMA.lock) < 0) {
		return -ERESTARTSYS;
	}

	for (controllerIdx = 0; controllerIdx < DMA_NUM_CONTROLLERS;
	     controllerIdx++) {
		for (channelIdx = 0; channelIdx < DMA_NUM_CHANNELS;
		     channelIdx++) {
			if (len >= limit) {
				break;
			}

			channel =
			    &gDMA.controller[controllerIdx].channel[channelIdx];

			len +=
			    sprintf(buf + len, "%d:%d ", controllerIdx,
				    channelIdx);

			if ((channel->flags & DMA_CHANNEL_FLAG_IS_DEDICATED) !=
			    0) {
				len +=
				    sprintf(buf + len, "Dedicated for %s ",
					    DMA_gDeviceAttribute[channel->
								 devType].name);
			} else {
				len += sprintf(buf + len, "Shared ");
			}

			if ((channel->flags & DMA_CHANNEL_FLAG_NO_ISR) != 0) {
				len += sprintf(buf + len, "No ISR ");
			}

			if ((channel->flags & DMA_CHANNEL_FLAG_LARGE_FIFO) != 0) {
				len += sprintf(buf + len, "Fifo: 128 ");
			} else {
				len += sprintf(buf + len, "Fifo: 64  ");
			}

			if ((channel->flags & DMA_CHANNEL_FLAG_IN_USE) != 0) {
				len +=
				    sprintf(buf + len, "InUse by %s",
					    DMA_gDeviceAttribute[channel->
								 devType].name);
#if (DMA_DEBUG_TRACK_RESERVATION)
				len +=
				    sprintf(buf + len, " (%s:%d)",
					    channel->fileName,
					    channel->lineNum);
#endif
			} else {
				len += sprintf(buf + len, "Avail ");
			}

			if (channel->lastDevType != DMA_DEVICE_NONE) {
				len +=
				    sprintf(buf + len, "Last use: %s ",
					    DMA_gDeviceAttribute[channel->
								 lastDevType].
					    name);
			}

			len += sprintf(buf + len, "\n");
		}
	}
	up(&gDMA.lock);
	*eof = 1;

	return len;
}