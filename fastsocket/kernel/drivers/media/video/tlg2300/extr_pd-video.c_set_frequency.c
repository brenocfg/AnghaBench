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
struct running_context {int freq; } ;
struct TYPE_2__ {struct running_context context; } ;
struct poseidon {int /*<<< orphan*/  lock; TYPE_1__ video_data; } ;
typedef  int s32 ;
typedef  int __u32 ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  TAKE_REQUEST ; 
 int TUNER_FREQ_MAX ; 
 int TUNER_FREQ_MIN ; 
 int /*<<< orphan*/  TUNE_FREQ_SELECT ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int send_set_req (struct poseidon*,int /*<<< orphan*/ ,int,int*) ; 

__attribute__((used)) static int set_frequency(struct poseidon *pd, __u32 frequency)
{
	s32 ret = 0, param, cmd_status;
	struct running_context *context = &pd->video_data.context;

	param = frequency * 62500 / 1000;
	if (param < TUNER_FREQ_MIN/1000 || param > TUNER_FREQ_MAX / 1000)
		return -EINVAL;

	mutex_lock(&pd->lock);
	ret = send_set_req(pd, TUNE_FREQ_SELECT, param, &cmd_status);
	ret = send_set_req(pd, TAKE_REQUEST, 0, &cmd_status);

	msleep(250); /* wait for a while until the hardware is ready. */
	context->freq = frequency;
	mutex_unlock(&pd->lock);
	return ret;
}