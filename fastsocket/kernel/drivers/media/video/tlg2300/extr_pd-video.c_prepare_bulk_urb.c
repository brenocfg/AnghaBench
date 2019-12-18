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
struct video_data {int /*<<< orphan*/  front; int /*<<< orphan*/  endpoint_addr; TYPE_1__* pd; scalar_t__* urb_array; } ;
struct TYPE_2__ {int /*<<< orphan*/  udev; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  SBUF_NUM ; 
 int /*<<< orphan*/  alloc_bulk_urbs_generic (scalar_t__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  urb_complete_bulk ; 

__attribute__((used)) static int prepare_bulk_urb(struct video_data *video)
{
	if (video->urb_array[0])
		return 0;

	alloc_bulk_urbs_generic(video->urb_array, SBUF_NUM,
			video->pd->udev, video->endpoint_addr,
			0x2000, GFP_KERNEL,
			urb_complete_bulk, video->front);
	return 0;
}