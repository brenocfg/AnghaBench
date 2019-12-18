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
struct scsi_device {int dummy; } ;
struct hp_sw_dh_data {scalar_t__ path_state; int /*<<< orphan*/ * callback_data; int /*<<< orphan*/  (* callback_fn ) (void*,int) ;int /*<<< orphan*/  retries; int /*<<< orphan*/  retry_cnt; } ;
typedef  int /*<<< orphan*/  (* activate_complete ) (void*,int) ;

/* Variables and functions */
 scalar_t__ HP_SW_PATH_PASSIVE ; 
 int SCSI_DH_OK ; 
 struct hp_sw_dh_data* get_hp_sw_data (struct scsi_device*) ; 
 int hp_sw_start_stop (struct hp_sw_dh_data*) ; 
 int hp_sw_tur (struct scsi_device*,struct hp_sw_dh_data*) ; 

__attribute__((used)) static int hp_sw_activate(struct scsi_device *sdev,
				activate_complete fn, void *data)
{
	int ret = SCSI_DH_OK;
	struct hp_sw_dh_data *h = get_hp_sw_data(sdev);

	ret = hp_sw_tur(sdev, h);

	if (ret == SCSI_DH_OK && h->path_state == HP_SW_PATH_PASSIVE) {
		h->retry_cnt = h->retries;
		h->callback_fn = fn;
		h->callback_data = data;
		ret = hp_sw_start_stop(h);
		if (ret == SCSI_DH_OK)
			return 0;
		h->callback_fn = h->callback_data = NULL;
	}

	if (fn)
		fn(data, ret);
	return 0;
}