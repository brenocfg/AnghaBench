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
struct video_data {int /*<<< orphan*/  bubble_work; } ;
struct poseidon {scalar_t__ cur_transfer_mode; struct video_data video_data; } ;
typedef  int /*<<< orphan*/  s32 ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PLAY_SERVICE ; 
 int /*<<< orphan*/  TAKE_REQUEST ; 
 int /*<<< orphan*/  TLG_TUNE_PLAY_SVC_START ; 
 int /*<<< orphan*/  fire_all_urb (struct video_data*) ; 
 int /*<<< orphan*/  iso_bubble_handler ; 
 int /*<<< orphan*/  prepare_bulk_urb (struct video_data*) ; 
 int /*<<< orphan*/  prepare_iso_urb (struct video_data*) ; 
 int /*<<< orphan*/  send_set_req (struct poseidon*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int start_video_stream(struct poseidon *pd)
{
	struct video_data *video = &pd->video_data;
	s32 cmd_status;

	send_set_req(pd, TAKE_REQUEST, 0, &cmd_status);
	send_set_req(pd, PLAY_SERVICE, TLG_TUNE_PLAY_SVC_START, &cmd_status);

	if (pd->cur_transfer_mode) {
		prepare_iso_urb(video);
		INIT_WORK(&video->bubble_work, iso_bubble_handler);
	} else {
		/* The bulk mode does not need a bubble handler */
		prepare_bulk_urb(video);
	}
	fire_all_urb(video);
	return 0;
}