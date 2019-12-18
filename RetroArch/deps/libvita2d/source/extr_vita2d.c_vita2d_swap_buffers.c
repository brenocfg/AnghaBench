#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  address; } ;
typedef  TYPE_1__ vita2d_display_data ;

/* Variables and functions */
 size_t DISPLAY_BUFFER_COUNT ; 
 size_t backBufferIndex ; 
 int /*<<< orphan*/ * displayBufferData ; 
 int /*<<< orphan*/ * displayBufferSync ; 
 int /*<<< orphan*/ * displaySurface ; 
 size_t frontBufferIndex ; 
 int /*<<< orphan*/  sceGxmDisplayQueueAddEntry (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  sceGxmPadHeartbeat (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void vita2d_swap_buffers()
{
	sceGxmPadHeartbeat(&displaySurface[backBufferIndex], displayBufferSync[backBufferIndex]);

	// queue the display swap for this frame
	vita2d_display_data displayData;
	displayData.address = displayBufferData[backBufferIndex];
	sceGxmDisplayQueueAddEntry(
		displayBufferSync[frontBufferIndex],	// OLD fb
		displayBufferSync[backBufferIndex],	// NEW fb
		&displayData);

	// update buffer indices
	frontBufferIndex = backBufferIndex;
	backBufferIndex = (backBufferIndex + 1) % DISPLAY_BUFFER_COUNT;
}