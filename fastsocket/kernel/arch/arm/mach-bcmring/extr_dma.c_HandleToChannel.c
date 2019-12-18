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
struct TYPE_4__ {TYPE_1__* controller; } ;
struct TYPE_3__ {int /*<<< orphan*/ * channel; } ;
typedef  int /*<<< orphan*/  DMA_Handle_t ;
typedef  int /*<<< orphan*/  DMA_Channel_t ;

/* Variables and functions */
 int CHANNEL_FROM_HANDLE (int /*<<< orphan*/ ) ; 
 int CONTROLLER_FROM_HANDLE (int /*<<< orphan*/ ) ; 
 int DMA_NUM_CHANNELS ; 
 int DMA_NUM_CONTROLLERS ; 
 TYPE_2__ gDMA ; 

__attribute__((used)) static inline DMA_Channel_t *HandleToChannel(DMA_Handle_t handle)
{
	int controllerIdx;
	int channelIdx;

	controllerIdx = CONTROLLER_FROM_HANDLE(handle);
	channelIdx = CHANNEL_FROM_HANDLE(handle);

	if ((controllerIdx > DMA_NUM_CONTROLLERS)
	    || (channelIdx > DMA_NUM_CHANNELS)) {
		return NULL;
	}
	return &gDMA.controller[controllerIdx].channel[channelIdx];
}