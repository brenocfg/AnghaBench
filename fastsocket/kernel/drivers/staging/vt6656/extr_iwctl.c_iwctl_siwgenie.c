#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct net_device {int dummy; } ;
struct iw_request_info {int dummy; } ;
struct iw_point {int length; } ;
struct TYPE_3__ {char wWPAIELen; int /*<<< orphan*/  abyWPAIE; } ;
struct TYPE_4__ {TYPE_1__ sMgmtObj; } ;
typedef  TYPE_1__* PSMgmtObject ;
typedef  TYPE_2__* PSDevice ;

/* Variables and functions */
 int EFAULT ; 
 int EINVAL ; 
 int ENOMEM ; 
 char MAX_WPA_IE_LEN ; 
 scalar_t__ copy_from_user (int /*<<< orphan*/ ,char*,char) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char) ; 
 int /*<<< orphan*/  netdev_priv (struct net_device*) ; 

int iwctl_siwgenie(struct net_device *dev,
			  struct iw_request_info *info,
			  struct iw_point *wrq,
			  char *extra)
{
	PSDevice			pDevice = (PSDevice)netdev_priv(dev);
	PSMgmtObject	pMgmt = &(pDevice->sMgmtObj);
	int ret=0;

	if(wrq->length){
		if ((wrq->length < 2) || (extra[1]+2 != wrq->length)) {
			ret = -EINVAL;
			goto out;
		}
		if(wrq->length > MAX_WPA_IE_LEN){
			ret = -ENOMEM;
			goto out;
		}
		memset(pMgmt->abyWPAIE, 0, MAX_WPA_IE_LEN);
		if(copy_from_user(pMgmt->abyWPAIE, extra, wrq->length)){
			ret = -EFAULT;
			goto out;
		}
		pMgmt->wWPAIELen = wrq->length;
	}else {
		memset(pMgmt->abyWPAIE, 0, MAX_WPA_IE_LEN);
		pMgmt->wWPAIELen = 0;
	}

	out://not completely ...not necessary in wpa_supplicant 0.5.8
	return 0;
}