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
struct TYPE_4__ {int length; } ;
union iwreq_data {TYPE_1__ data; } ;
struct net_device {TYPE_3__* ml_priv; } ;
struct iw_request_info {int dummy; } ;
typedef  scalar_t__ UCHAR ;
struct TYPE_5__ {int RSNIE_Len; scalar_t__ AuthMode; scalar_t__ WpaSupplicantUP; int /*<<< orphan*/ * RSN_IE; } ;
struct TYPE_6__ {TYPE_2__ StaCfg; } ;
typedef  TYPE_3__* PRTMP_ADAPTER ;

/* Variables and functions */
 int E2BIG ; 
 scalar_t__ IE_RSN ; 
 scalar_t__ IE_WPA ; 
 scalar_t__ Ndis802_11AuthModeWPA ; 
 scalar_t__ Ndis802_11AuthModeWPA2 ; 
 scalar_t__ Ndis802_11AuthModeWPA2PSK ; 
 scalar_t__ WPA_SUPPLICANT_ENABLE ; 
 int /*<<< orphan*/  memcpy (char*,int /*<<< orphan*/ *,int) ; 

int rt_ioctl_giwgenie(struct net_device *dev,
			       struct iw_request_info *info,
			       union iwreq_data *wrqu, char *extra)
{
	PRTMP_ADAPTER   pAd = dev->ml_priv;

	if ((pAd->StaCfg.RSNIE_Len == 0) ||
		(pAd->StaCfg.AuthMode < Ndis802_11AuthModeWPA))
	{
		wrqu->data.length = 0;
		return 0;
	}

	if (pAd->StaCfg.WpaSupplicantUP == WPA_SUPPLICANT_ENABLE)
	{
	if (wrqu->data.length < pAd->StaCfg.RSNIE_Len)
		return -E2BIG;

	wrqu->data.length = pAd->StaCfg.RSNIE_Len;
	memcpy(extra, &pAd->StaCfg.RSN_IE[0], pAd->StaCfg.RSNIE_Len);
	}
	else
	{
		UCHAR RSNIe = IE_WPA;

		if (wrqu->data.length < (pAd->StaCfg.RSNIE_Len + 2)) // ID, Len
			return -E2BIG;
		wrqu->data.length = pAd->StaCfg.RSNIE_Len + 2;

		if ((pAd->StaCfg.AuthMode == Ndis802_11AuthModeWPA2PSK) ||
            (pAd->StaCfg.AuthMode == Ndis802_11AuthModeWPA2))
			RSNIe = IE_RSN;

		extra[0] = (char)RSNIe;
		extra[1] = pAd->StaCfg.RSNIE_Len;
		memcpy(extra+2, &pAd->StaCfg.RSN_IE[0], pAd->StaCfg.RSNIE_Len);
	}

	return 0;
}