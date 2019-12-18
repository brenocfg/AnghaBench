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
struct video_data {scalar_t__* urb_array; scalar_t__ is_streaming; struct poseidon* pd; } ;
struct poseidon {int dummy; } ;
typedef  int /*<<< orphan*/  s32 ;

/* Variables and functions */
 int /*<<< orphan*/  PLAY_SERVICE ; 
 int SBUF_NUM ; 
 int /*<<< orphan*/  TLG_TUNE_PLAY_SVC_STOP ; 
 int /*<<< orphan*/  send_set_req (struct poseidon*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usb_kill_urb (scalar_t__) ; 

__attribute__((used)) static int usb_transfer_stop(struct video_data *video)
{
	if (video->is_streaming) {
		int i;
		s32 cmd_status;
		struct poseidon *pd = video->pd;

		video->is_streaming = 0;
		for (i = 0; i < SBUF_NUM; ++i) {
			if (video->urb_array[i])
				usb_kill_urb(video->urb_array[i]);
		}

		send_set_req(pd, PLAY_SERVICE, TLG_TUNE_PLAY_SVC_STOP,
			       &cmd_status);
	}
	return 0;
}