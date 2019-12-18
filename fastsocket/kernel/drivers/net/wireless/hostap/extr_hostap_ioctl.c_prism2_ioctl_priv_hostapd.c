#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct prism2_hostapd_param {int cmd; } ;
struct iw_point {int length; int /*<<< orphan*/  pointer; } ;
struct TYPE_11__ {int /*<<< orphan*/  ap; } ;
typedef  TYPE_1__ local_info_t ;

/* Variables and functions */
 int EFAULT ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
#define  PRISM2_GET_ENCRYPTION 135 
#define  PRISM2_HOSTAPD_GET_RID 134 
 int PRISM2_HOSTAPD_MAX_BUF_SIZE ; 
#define  PRISM2_HOSTAPD_MLME 133 
#define  PRISM2_HOSTAPD_SCAN_REQ 132 
#define  PRISM2_HOSTAPD_SET_ASSOC_AP_ADDR 131 
#define  PRISM2_HOSTAPD_SET_GENERIC_ELEMENT 130 
#define  PRISM2_HOSTAPD_SET_RID 129 
#define  PRISM2_SET_ENCRYPTION 128 
 scalar_t__ copy_from_user (struct prism2_hostapd_param*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ copy_to_user (int /*<<< orphan*/ ,struct prism2_hostapd_param*,int) ; 
 int /*<<< orphan*/  kfree (struct prism2_hostapd_param*) ; 
 struct prism2_hostapd_param* kmalloc (int,int /*<<< orphan*/ ) ; 
 int prism2_hostapd (int /*<<< orphan*/ ,struct prism2_hostapd_param*) ; 
 int prism2_ioctl_get_encryption (TYPE_1__*,struct prism2_hostapd_param*,int) ; 
 int prism2_ioctl_get_rid (TYPE_1__*,struct prism2_hostapd_param*,int) ; 
 int prism2_ioctl_mlme (TYPE_1__*,struct prism2_hostapd_param*) ; 
 int prism2_ioctl_scan_req (TYPE_1__*,struct prism2_hostapd_param*) ; 
 int prism2_ioctl_set_assoc_ap_addr (TYPE_1__*,struct prism2_hostapd_param*,int) ; 
 int prism2_ioctl_set_encryption (TYPE_1__*,struct prism2_hostapd_param*,int) ; 
 int prism2_ioctl_set_generic_element (TYPE_1__*,struct prism2_hostapd_param*,int) ; 
 int prism2_ioctl_set_rid (TYPE_1__*,struct prism2_hostapd_param*,int) ; 

__attribute__((used)) static int prism2_ioctl_priv_hostapd(local_info_t *local, struct iw_point *p)
{
	struct prism2_hostapd_param *param;
	int ret = 0;
	int ap_ioctl = 0;

	if (p->length < sizeof(struct prism2_hostapd_param) ||
	    p->length > PRISM2_HOSTAPD_MAX_BUF_SIZE || !p->pointer)
		return -EINVAL;

	param = kmalloc(p->length, GFP_KERNEL);
	if (param == NULL)
		return -ENOMEM;

	if (copy_from_user(param, p->pointer, p->length)) {
		ret = -EFAULT;
		goto out;
	}

	switch (param->cmd) {
	case PRISM2_SET_ENCRYPTION:
		ret = prism2_ioctl_set_encryption(local, param, p->length);
		break;
	case PRISM2_GET_ENCRYPTION:
		ret = prism2_ioctl_get_encryption(local, param, p->length);
		break;
	case PRISM2_HOSTAPD_GET_RID:
		ret = prism2_ioctl_get_rid(local, param, p->length);
		break;
	case PRISM2_HOSTAPD_SET_RID:
		ret = prism2_ioctl_set_rid(local, param, p->length);
		break;
	case PRISM2_HOSTAPD_SET_ASSOC_AP_ADDR:
		ret = prism2_ioctl_set_assoc_ap_addr(local, param, p->length);
		break;
	case PRISM2_HOSTAPD_SET_GENERIC_ELEMENT:
		ret = prism2_ioctl_set_generic_element(local, param,
						       p->length);
		break;
	case PRISM2_HOSTAPD_MLME:
		ret = prism2_ioctl_mlme(local, param);
		break;
	case PRISM2_HOSTAPD_SCAN_REQ:
		ret = prism2_ioctl_scan_req(local, param);
		break;
	default:
		ret = prism2_hostapd(local->ap, param);
		ap_ioctl = 1;
		break;
	}

	if (ret == 1 || !ap_ioctl) {
		if (copy_to_user(p->pointer, param, p->length)) {
			ret = -EFAULT;
			goto out;
		} else if (ap_ioctl)
			ret = 0;
	}

 out:
	kfree(param);
	return ret;
}