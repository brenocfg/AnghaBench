#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  sa_family; int /*<<< orphan*/  sa_data; } ;
union iwreq_data {TYPE_1__ ap_addr; } ;
typedef  scalar_t__ u16 ;
struct airo_info {scalar_t__ scan_timeout; TYPE_2__* dev; int /*<<< orphan*/  thr_wait; scalar_t__ expires; int /*<<< orphan*/  jobs; int /*<<< orphan*/  sem; int /*<<< orphan*/  flags; scalar_t__ list_bss_task; } ;
struct TYPE_5__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARPHRD_ETHER ; 
 int /*<<< orphan*/  ETH_ALEN ; 
 int /*<<< orphan*/  EVACK ; 
 int /*<<< orphan*/  EV_LINK ; 
 int /*<<< orphan*/  FLAG_UPDATE_MULTI ; 
 int /*<<< orphan*/  FLAG_UPDATE_UNI ; 
 int HZ ; 
 int /*<<< orphan*/  IN4500 (struct airo_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  JOB_EVENT ; 
 int /*<<< orphan*/  LINKSTAT ; 
 int /*<<< orphan*/  OUT4500 (struct airo_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ RUN_AT (int) ; 
 int /*<<< orphan*/  SIOCGIWAP ; 
 scalar_t__ STAT_ASSOC ; 
 scalar_t__ STAT_FORCELOSS ; 
 scalar_t__ STAT_REASSOC ; 
 int /*<<< orphan*/  airo_print_status (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  airo_send_event (TYPE_2__*) ; 
 scalar_t__ auto_wep ; 
 scalar_t__ down_trylock (int /*<<< orphan*/ *) ; 
 scalar_t__ le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,char,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wake_up_interruptible (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wake_up_process (scalar_t__) ; 
 int /*<<< orphan*/  wireless_send_event (TYPE_2__*,int /*<<< orphan*/ ,union iwreq_data*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void airo_handle_link(struct airo_info *ai)
{
	union iwreq_data wrqu;
	int scan_forceloss = 0;
	u16 status;

	/* Get new status and acknowledge the link change */
	status = le16_to_cpu(IN4500(ai, LINKSTAT));
	OUT4500(ai, EVACK, EV_LINK);

	if ((status == STAT_FORCELOSS) && (ai->scan_timeout > 0))
		scan_forceloss = 1;

	airo_print_status(ai->dev->name, status);

	if ((status == STAT_ASSOC) || (status == STAT_REASSOC)) {
		if (auto_wep)
			ai->expires = 0;
		if (ai->list_bss_task)
			wake_up_process(ai->list_bss_task);
		set_bit(FLAG_UPDATE_UNI, &ai->flags);
		set_bit(FLAG_UPDATE_MULTI, &ai->flags);

		if (down_trylock(&ai->sem) != 0) {
			set_bit(JOB_EVENT, &ai->jobs);
			wake_up_interruptible(&ai->thr_wait);
		} else
			airo_send_event(ai->dev);
	} else if (!scan_forceloss) {
		if (auto_wep && !ai->expires) {
			ai->expires = RUN_AT(3*HZ);
			wake_up_interruptible(&ai->thr_wait);
		}

		/* Send event to user space */
		memset(wrqu.ap_addr.sa_data, '\0', ETH_ALEN);
		wrqu.ap_addr.sa_family = ARPHRD_ETHER;
		wireless_send_event(ai->dev, SIOCGIWAP, &wrqu, NULL);
	}
}