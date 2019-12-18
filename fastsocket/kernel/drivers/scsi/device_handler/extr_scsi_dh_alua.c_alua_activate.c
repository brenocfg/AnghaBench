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
struct alua_dh_data {int tpgs; int state; int flags; int /*<<< orphan*/ * callback_data; int /*<<< orphan*/  (* callback_fn ) (void*,int) ;int /*<<< orphan*/  pref; } ;
typedef  int /*<<< orphan*/  (* activate_complete ) (void*,int) ;

/* Variables and functions */
 int ALUA_OPTIMIZE_STPG ; 
 int SCSI_DH_IO ; 
 int SCSI_DH_OK ; 
 int SCSI_DH_RETRY ; 
 int TPGS_MODE_EXPLICIT ; 
 int TPGS_MODE_IMPLICIT ; 
#define  TPGS_STATE_NONOPTIMIZED 132 
#define  TPGS_STATE_OFFLINE 131 
#define  TPGS_STATE_STANDBY 130 
#define  TPGS_STATE_TRANSITIONING 129 
#define  TPGS_STATE_UNAVAILABLE 128 
 int alua_rtpg (struct scsi_device*,struct alua_dh_data*) ; 
 struct alua_dh_data* get_alua_data (struct scsi_device*) ; 
 int submit_stpg (struct alua_dh_data*) ; 

__attribute__((used)) static int alua_activate(struct scsi_device *sdev,
			activate_complete fn, void *data)
{
	struct alua_dh_data *h = get_alua_data(sdev);
	int err = SCSI_DH_OK;
	int stpg = 0;

	err = alua_rtpg(sdev, h);
	if (err != SCSI_DH_OK)
		goto out;

	if (h->tpgs & TPGS_MODE_EXPLICIT) {
		switch (h->state) {
		case TPGS_STATE_NONOPTIMIZED:
			stpg = 1;
			if ((h->flags & ALUA_OPTIMIZE_STPG) &&
			    (!h->pref) &&
			    (h->tpgs & TPGS_MODE_IMPLICIT))
				stpg = 0;
			break;
		case TPGS_STATE_STANDBY:
		case TPGS_STATE_UNAVAILABLE:
			stpg = 1;
			break;
		case TPGS_STATE_OFFLINE:
			err = SCSI_DH_IO;
			break;
		case TPGS_STATE_TRANSITIONING:
			err = SCSI_DH_RETRY;
			break;
		default:
			break;
		}
	}

	if (stpg) {
		h->callback_fn = fn;
		h->callback_data = data;
		err = submit_stpg(h);
		if (err == SCSI_DH_OK)
			return 0;
		h->callback_fn = h->callback_data = NULL;
	}

out:
	if (fn)
		fn(data, err);
	return 0;
}