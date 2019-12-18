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
struct pwc_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SET_EP_STREAM_CTL ; 
 int /*<<< orphan*/  VIDEO_OUTPUT_CONTROL_FORMATTER ; 
 int _send_control_msg (struct pwc_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,void*,int,int) ; 

__attribute__((used)) static inline int send_video_command(struct pwc_device *pdev,
	int index, void *buf, int buflen)
{
	return _send_control_msg(pdev,
		SET_EP_STREAM_CTL,
		VIDEO_OUTPUT_CONTROL_FORMATTER,
		index,
		buf, buflen, 1000);
}