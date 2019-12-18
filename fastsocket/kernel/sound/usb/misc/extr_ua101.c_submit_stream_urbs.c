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
struct ua101_stream {unsigned int queue_length; TYPE_1__** urbs; } ;
struct ua101 {TYPE_2__* dev; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;
struct TYPE_3__ {int /*<<< orphan*/  urb; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_error_string (int) ; 
 int usb_submit_urb (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int submit_stream_urbs(struct ua101 *ua, struct ua101_stream *stream)
{
	unsigned int i;

	for (i = 0; i < stream->queue_length; ++i) {
		int err = usb_submit_urb(&stream->urbs[i]->urb, GFP_KERNEL);
		if (err < 0) {
			dev_err(&ua->dev->dev, "USB request error %d: %s\n",
				err, usb_error_string(err));
			return err;
		}
	}
	return 0;
}