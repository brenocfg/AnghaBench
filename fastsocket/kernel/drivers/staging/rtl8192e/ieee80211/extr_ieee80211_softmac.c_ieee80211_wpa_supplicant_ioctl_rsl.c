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
struct iw_point {int length; int /*<<< orphan*/  pointer; } ;
struct TYPE_5__ {int /*<<< orphan*/  reason_code; int /*<<< orphan*/  command; } ;
struct TYPE_4__ {int /*<<< orphan*/  value; int /*<<< orphan*/  name; } ;
struct TYPE_6__ {TYPE_2__ mlme; TYPE_1__ wpa_param; } ;
struct ieee_param {int cmd; TYPE_3__ u; } ;
struct ieee80211_device {int /*<<< orphan*/  wx_sem; } ;

/* Variables and functions */
 int EFAULT ; 
 int EINVAL ; 
 int ENOMEM ; 
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
#define  IEEE_CMD_MLME 131 
#define  IEEE_CMD_SET_ENCRYPTION 130 
#define  IEEE_CMD_SET_WPA_IE 129 
#define  IEEE_CMD_SET_WPA_PARAM 128 
 scalar_t__ copy_from_user (struct ieee_param*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ copy_to_user (int /*<<< orphan*/ ,struct ieee_param*,int) ; 
 int /*<<< orphan*/  down (int /*<<< orphan*/ *) ; 
 int ieee80211_wpa_mlme (struct ieee80211_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ieee80211_wpa_set_encryption (struct ieee80211_device*,struct ieee_param*,int) ; 
 int ieee80211_wpa_set_param (struct ieee80211_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ieee80211_wpa_set_wpa_ie (struct ieee80211_device*,struct ieee_param*,int) ; 
 int /*<<< orphan*/  kfree (struct ieee_param*) ; 
 scalar_t__ kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printk (char*,int) ; 
 int /*<<< orphan*/  up (int /*<<< orphan*/ *) ; 

int ieee80211_wpa_supplicant_ioctl(struct ieee80211_device *ieee, struct iw_point *p)
{
	struct ieee_param *param;
	int ret=0;

	down(&ieee->wx_sem);
	//IEEE_DEBUG_INFO("wpa_supplicant: len=%d\n", p->length);

	if (p->length < sizeof(struct ieee_param) || !p->pointer){
		ret = -EINVAL;
		goto out;
	}

	param = (struct ieee_param *)kmalloc(p->length, GFP_KERNEL);
	if (param == NULL){
		ret = -ENOMEM;
		goto out;
	}
	if (copy_from_user(param, p->pointer, p->length)) {
		kfree(param);
		ret = -EFAULT;
		goto out;
	}

	switch (param->cmd) {

	case IEEE_CMD_SET_WPA_PARAM:
		ret = ieee80211_wpa_set_param(ieee, param->u.wpa_param.name,
					param->u.wpa_param.value);
		break;

	case IEEE_CMD_SET_WPA_IE:
		ret = ieee80211_wpa_set_wpa_ie(ieee, param, p->length);
		break;

	case IEEE_CMD_SET_ENCRYPTION:
		ret = ieee80211_wpa_set_encryption(ieee, param, p->length);
		break;

	case IEEE_CMD_MLME:
		ret = ieee80211_wpa_mlme(ieee, param->u.mlme.command,
				   param->u.mlme.reason_code);
		break;

	default:
		printk("Unknown WPA supplicant request: %d\n",param->cmd);
		ret = -EOPNOTSUPP;
		break;
	}

	if (ret == 0 && copy_to_user(p->pointer, param, p->length))
		ret = -EFAULT;

	kfree(param);
out:
	up(&ieee->wx_sem);

	return ret;
}