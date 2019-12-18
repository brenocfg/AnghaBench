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
struct TYPE_2__ {int pre_emphasis; int is_radio_streaming; int fm_freq; } ;
struct poseidon {int /*<<< orphan*/  lock; TYPE_1__ radio_data; } ;
typedef  int __u32 ;

/* Variables and functions */
 int EINVAL ; 
 int HZ ; 
 int /*<<< orphan*/  PLAY_SERVICE ; 
 int /*<<< orphan*/  TAKE_REQUEST ; 
 int /*<<< orphan*/  TASK_INTERRUPTIBLE ; 
 int TLG_TUNE_PLAY_SVC_START ; 
 int /*<<< orphan*/  TUNER_AUD_ANA_STD ; 
 int TUNER_FREQ_MAX_FM ; 
 int TUNER_FREQ_MIN_FM ; 
 int /*<<< orphan*/  TUNE_FREQ_SELECT ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  schedule_timeout (int) ; 
 int send_set_req (struct poseidon*,int /*<<< orphan*/ ,int,int*) ; 
 int /*<<< orphan*/  set_current_state (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int set_frequency(struct poseidon *p, __u32 frequency)
{
	__u32 freq ;
	int ret, status;

	mutex_lock(&p->lock);

	ret = send_set_req(p, TUNER_AUD_ANA_STD,
				p->radio_data.pre_emphasis, &status);

	freq =  (frequency * 125) * 500 / 1000;/* kHZ */
	if (freq < TUNER_FREQ_MIN_FM/1000 || freq > TUNER_FREQ_MAX_FM/1000) {
		ret = -EINVAL;
		goto error;
	}

	ret = send_set_req(p, TUNE_FREQ_SELECT, freq, &status);
	if (ret < 0)
		goto error ;
	ret = send_set_req(p, TAKE_REQUEST, 0, &status);

	set_current_state(TASK_INTERRUPTIBLE);
	schedule_timeout(HZ/4);
	if (!p->radio_data.is_radio_streaming) {
		ret = send_set_req(p, TAKE_REQUEST, 0, &status);
		ret = send_set_req(p, PLAY_SERVICE,
				TLG_TUNE_PLAY_SVC_START, &status);
		p->radio_data.is_radio_streaming = 1;
	}
	p->radio_data.fm_freq = frequency;
error:
	mutex_unlock(&p->lock);
	return ret;
}