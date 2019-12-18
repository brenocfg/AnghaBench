#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int audio_idx; int /*<<< orphan*/  tvnormid; } ;
struct TYPE_5__ {TYPE_1__ context; } ;
struct poseidon {int /*<<< orphan*/  lock; TYPE_2__ video_data; } ;
typedef  int s32 ;
struct TYPE_6__ {int tlg_audio_mode; } ;

/* Variables and functions */
 int /*<<< orphan*/  TUNER_AUD_ANA_STD ; 
 int /*<<< orphan*/  TUNER_AUD_MODE ; 
 int get_audio_std (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 TYPE_3__* pd_audio_modes ; 
 int send_set_req (struct poseidon*,int /*<<< orphan*/ ,int,int*) ; 

__attribute__((used)) static int pd_vidioc_s_tuner(struct poseidon *pd, int index)
{
	s32 ret = 0, cmd_status, param, audiomode;

	mutex_lock(&pd->lock);
	param = pd_audio_modes[index].tlg_audio_mode;
	ret = send_set_req(pd, TUNER_AUD_MODE, param, &cmd_status);
	audiomode = get_audio_std(pd->video_data.context.tvnormid);
	ret |= send_set_req(pd, TUNER_AUD_ANA_STD, audiomode,
				&cmd_status);
	if (!ret)
		pd->video_data.context.audio_idx = index;
	mutex_unlock(&pd->lock);
	return ret;
}