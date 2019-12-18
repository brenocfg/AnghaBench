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
struct poseidon {int /*<<< orphan*/  lock; } ;
struct pd_dvb_adapter {scalar_t__* urb_array; scalar_t__ is_streaming; struct poseidon* pd_device; } ;
typedef  size_t s32 ;

/* Variables and functions */
 size_t DVB_SBUF_NUM ; 
 int /*<<< orphan*/  PLAY_SERVICE ; 
 int /*<<< orphan*/  TLG_TUNE_PLAY_SVC_STOP ; 
 int /*<<< orphan*/  log (char*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 size_t send_set_req (struct poseidon*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t*) ; 
 int /*<<< orphan*/  usb_kill_urb (scalar_t__) ; 

void dvb_stop_streaming(struct pd_dvb_adapter *pd_dvb)
{
	struct poseidon *pd = pd_dvb->pd_device;

	mutex_lock(&pd->lock);
	if (pd_dvb->is_streaming) {
		s32 i, ret, cmd_status = 0;

		pd_dvb->is_streaming = 0;

		for (i = 0; i < DVB_SBUF_NUM; i++)
			if (pd_dvb->urb_array[i])
				usb_kill_urb(pd_dvb->urb_array[i]);

		ret = send_set_req(pd, PLAY_SERVICE, TLG_TUNE_PLAY_SVC_STOP,
					&cmd_status);
		if (ret | cmd_status)
			log("error");
	}
	mutex_unlock(&pd->lock);
}