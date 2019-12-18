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
struct iw_point {int length; int flags; } ;
union iwreq_data {struct iw_point encoding; } ;
struct net_device {TYPE_3__* ml_priv; } ;
struct iw_request_info {int dummy; } ;
struct iw_encode_ext {int key_len; int /*<<< orphan*/  key; int /*<<< orphan*/  alg; } ;
struct TYPE_5__ {int WepStatus; int DefaultKeyId; int /*<<< orphan*/ * PMK; } ;
struct TYPE_6__ {TYPE_2__ StaCfg; TYPE_1__** SharedKey; } ;
struct TYPE_4__ {int KeyLen; int /*<<< orphan*/ * Key; } ;
typedef  TYPE_3__* PRTMP_ADAPTER ;
typedef  int /*<<< orphan*/ * PCHAR ;

/* Variables and functions */
 size_t BSS0 ; 
 int /*<<< orphan*/  DBGPRINT (int /*<<< orphan*/ ,char*) ; 
 int E2BIG ; 
 int EINVAL ; 
 int /*<<< orphan*/  IW_ENCODE_ALG_CCMP ; 
 int /*<<< orphan*/  IW_ENCODE_ALG_NONE ; 
 int /*<<< orphan*/  IW_ENCODE_ALG_TKIP ; 
 int /*<<< orphan*/  IW_ENCODE_ALG_WEP ; 
 int IW_ENCODE_DISABLED ; 
 int IW_ENCODE_ENABLED ; 
 int IW_ENCODE_INDEX ; 
#define  Ndis802_11Encryption2Enabled 131 
#define  Ndis802_11Encryption3Enabled 130 
#define  Ndis802_11WEPDisabled 129 
#define  Ndis802_11WEPEnabled 128 
 int /*<<< orphan*/  RT_DEBUG_TRACE ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memset (struct iw_encode_ext*,int /*<<< orphan*/ ,int) ; 

int
rt_ioctl_giwencodeext(struct net_device *dev,
			  struct iw_request_info *info,
			  union iwreq_data *wrqu, char *extra)
{
	PRTMP_ADAPTER pAd = dev->ml_priv;
	PCHAR pKey = NULL;
	struct iw_point *encoding = &wrqu->encoding;
	struct iw_encode_ext *ext = (struct iw_encode_ext *)extra;
	int idx, max_key_len;

	DBGPRINT(RT_DEBUG_TRACE ,("===> rt_ioctl_giwencodeext\n"));

	max_key_len = encoding->length - sizeof(*ext);
	if (max_key_len < 0)
		return -EINVAL;

	idx = encoding->flags & IW_ENCODE_INDEX;
	if (idx)
	{
		if (idx < 1 || idx > 4)
			return -EINVAL;
		idx--;

		if ((pAd->StaCfg.WepStatus == Ndis802_11Encryption2Enabled) ||
			(pAd->StaCfg.WepStatus == Ndis802_11Encryption3Enabled))
		{
			if (idx != pAd->StaCfg.DefaultKeyId)
			{
				ext->key_len = 0;
				return 0;
			}
		}
	}
	else
		idx = pAd->StaCfg.DefaultKeyId;

	encoding->flags = idx + 1;
	memset(ext, 0, sizeof(*ext));

	ext->key_len = 0;
	switch(pAd->StaCfg.WepStatus) {
		case Ndis802_11WEPDisabled:
			ext->alg = IW_ENCODE_ALG_NONE;
			encoding->flags |= IW_ENCODE_DISABLED;
			break;
		case Ndis802_11WEPEnabled:
			ext->alg = IW_ENCODE_ALG_WEP;
			if (pAd->SharedKey[BSS0][idx].KeyLen > max_key_len)
				return -E2BIG;
			else
			{
				ext->key_len = pAd->SharedKey[BSS0][idx].KeyLen;
				pKey = &(pAd->SharedKey[BSS0][idx].Key[0]);
			}
			break;
		case Ndis802_11Encryption2Enabled:
		case Ndis802_11Encryption3Enabled:
			if (pAd->StaCfg.WepStatus == Ndis802_11Encryption2Enabled)
				ext->alg = IW_ENCODE_ALG_TKIP;
			else
				ext->alg = IW_ENCODE_ALG_CCMP;

			if (max_key_len < 32)
				return -E2BIG;
			else
			{
				ext->key_len = 32;
				pKey = &pAd->StaCfg.PMK[0];
			}
			break;
		default:
			return -EINVAL;
	}

	if (ext->key_len && pKey)
	{
		encoding->flags |= IW_ENCODE_ENABLED;
		memcpy(ext->key, pKey, ext->key_len);
	}

	return 0;
}