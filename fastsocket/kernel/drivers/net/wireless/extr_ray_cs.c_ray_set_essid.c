#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct net_device {int dummy; } ;
struct iw_request_info {int dummy; } ;
struct iw_point {scalar_t__ flags; int /*<<< orphan*/  length; } ;
struct TYPE_6__ {int /*<<< orphan*/  a_current_ess_id; } ;
struct TYPE_5__ {TYPE_2__ b5; } ;
struct TYPE_7__ {scalar_t__ card_status; TYPE_1__ sparm; } ;
typedef  TYPE_3__ ray_dev_t ;

/* Variables and functions */
 scalar_t__ CARD_AWAITING_PARAM ; 
 int E2BIG ; 
 int EBUSY ; 
 int EINPROGRESS ; 
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  IW_ESSID_MAX_SIZE ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_3__* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int ray_set_essid(struct net_device *dev,
			 struct iw_request_info *info,
			 struct iw_point *dwrq, char *extra)
{
	ray_dev_t *local = netdev_priv(dev);

	/* Reject if card is already initialised */
	if (local->card_status != CARD_AWAITING_PARAM)
		return -EBUSY;

	/* Check if we asked for `any' */
	if (dwrq->flags == 0) {
		/* Corey : can you do that ? */
		return -EOPNOTSUPP;
	} else {
		/* Check the size of the string */
		if (dwrq->length > IW_ESSID_MAX_SIZE) {
			return -E2BIG;
		}

		/* Set the ESSID in the card */
		memset(local->sparm.b5.a_current_ess_id, 0, IW_ESSID_MAX_SIZE);
		memcpy(local->sparm.b5.a_current_ess_id, extra, dwrq->length);
	}

	return -EINPROGRESS;	/* Call commit handler */
}