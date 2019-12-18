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
struct video_data {int is_streaming; int /*<<< orphan*/ * urb_array; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int SBUF_NUM ; 
 int /*<<< orphan*/  log (char*,int,int) ; 
 int usb_submit_urb (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int fire_all_urb(struct video_data *video)
{
	int i, ret;

	video->is_streaming = 1;

	for (i = 0; i < SBUF_NUM; i++) {
		ret = usb_submit_urb(video->urb_array[i], GFP_KERNEL);
		if (ret)
			log("(%d) failed: error %d", i, ret);
	}
	return ret;
}