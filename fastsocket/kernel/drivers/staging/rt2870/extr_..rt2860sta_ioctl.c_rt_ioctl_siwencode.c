#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct net_device {TYPE_3__* ml_priv; } ;
struct iw_request_info {int dummy; } ;
struct iw_point {scalar_t__ length; int flags; } ;
struct TYPE_7__ {int DefaultKeyId; void* WepStatus; void* AuthMode; void* OrigWepStatus; void* GroupCipher; void* PairCipher; } ;
struct TYPE_8__ {TYPE_2__ StaCfg; TYPE_1__** SharedKey; } ;
struct TYPE_6__ {scalar_t__ KeyLen; int /*<<< orphan*/  Key; int /*<<< orphan*/  CipherAlg; } ;
typedef  TYPE_3__* PRTMP_ADAPTER ;

/* Variables and functions */
 size_t BSS0 ; 
 int /*<<< orphan*/  CIPHER_WEP128 ; 
 int /*<<< orphan*/  CIPHER_WEP64 ; 
 int /*<<< orphan*/  DBGPRINT (int /*<<< orphan*/ ,char*) ; 
 int EINVAL ; 
 int ENETDOWN ; 
 int IW_ENCODE_DISABLED ; 
 int IW_ENCODE_INDEX ; 
 int IW_ENCODE_MODE ; 
 int IW_ENCODE_NOKEY ; 
 int IW_ENCODE_OPEN ; 
 int IW_ENCODE_RESTRICTED ; 
 scalar_t__ MAX_WEP_KEY_SIZE ; 
 scalar_t__ MIN_WEP_KEY_SIZE ; 
 int NR_WEP_KEYS ; 
 void* Ndis802_11AuthModeOpen ; 
 void* Ndis802_11AuthModeShared ; 
 void* Ndis802_11WEPDisabled ; 
 void* Ndis802_11WEPEnabled ; 
 int /*<<< orphan*/  NdisMoveMemory (int /*<<< orphan*/ ,char*,scalar_t__) ; 
 int /*<<< orphan*/  NdisZeroMemory (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  RTMP_TEST_FLAG (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RT_DEBUG_TRACE ; 
 int /*<<< orphan*/  STA_PORT_SECURED (TYPE_3__*) ; 
 int /*<<< orphan*/  fRTMP_ADAPTER_INTERRUPT_IN_USE ; 

int rt_ioctl_siwencode(struct net_device *dev,
			  struct iw_request_info *info,
			  struct iw_point *erq, char *extra)
{
	PRTMP_ADAPTER pAdapter = dev->ml_priv;

	//check if the interface is down
    	if(!RTMP_TEST_FLAG(pAdapter, fRTMP_ADAPTER_INTERRUPT_IN_USE))
    	{
      		DBGPRINT(RT_DEBUG_TRACE, ("INFO::Network is down!\n"));
        	return -ENETDOWN;
    	}

	if ((erq->length == 0) &&
        (erq->flags & IW_ENCODE_DISABLED))
	{
		pAdapter->StaCfg.PairCipher = Ndis802_11WEPDisabled;
		pAdapter->StaCfg.GroupCipher = Ndis802_11WEPDisabled;
		pAdapter->StaCfg.WepStatus = Ndis802_11WEPDisabled;
        pAdapter->StaCfg.OrigWepStatus = pAdapter->StaCfg.WepStatus;
        pAdapter->StaCfg.AuthMode = Ndis802_11AuthModeOpen;
        goto done;
	} else if (
		 (erq->flags & IW_ENCODE_RESTRICTED || erq->flags & IW_ENCODE_OPEN)) {
		STA_PORT_SECURED(pAdapter);
		pAdapter->StaCfg.PairCipher = Ndis802_11WEPEnabled;
		pAdapter->StaCfg.GroupCipher = Ndis802_11WEPEnabled;
		pAdapter->StaCfg.WepStatus = Ndis802_11WEPEnabled;
        pAdapter->StaCfg.OrigWepStatus = pAdapter->StaCfg.WepStatus;
		if (erq->flags & IW_ENCODE_RESTRICTED)
			pAdapter->StaCfg.AuthMode = Ndis802_11AuthModeShared;
    	else
			pAdapter->StaCfg.AuthMode = Ndis802_11AuthModeOpen;
	}

    if (erq->length > 0)
	{
		int keyIdx = (erq->flags & IW_ENCODE_INDEX) - 1;
		/* Check the size of the key */
		if (erq->length > MAX_WEP_KEY_SIZE) {
			return -EINVAL;
		}
		/* Check key index */
		if ((keyIdx < 0) || (keyIdx >= NR_WEP_KEYS))
        {
            DBGPRINT(RT_DEBUG_TRACE ,("==>rt_ioctl_siwencode::Wrong keyIdx=%d! Using default key instead (%d)\n",
                                        keyIdx, pAdapter->StaCfg.DefaultKeyId));

            //Using default key
			keyIdx = pAdapter->StaCfg.DefaultKeyId;
        }
		else
			pAdapter->StaCfg.DefaultKeyId=keyIdx;

        NdisZeroMemory(pAdapter->SharedKey[BSS0][keyIdx].Key,  16);

		if (erq->length == MAX_WEP_KEY_SIZE)
        {
			pAdapter->SharedKey[BSS0][keyIdx].KeyLen = MAX_WEP_KEY_SIZE;
            pAdapter->SharedKey[BSS0][keyIdx].CipherAlg = CIPHER_WEP128;
		}
		else if (erq->length == MIN_WEP_KEY_SIZE)
        {
            pAdapter->SharedKey[BSS0][keyIdx].KeyLen = MIN_WEP_KEY_SIZE;
            pAdapter->SharedKey[BSS0][keyIdx].CipherAlg = CIPHER_WEP64;
		}
		else
			/* Disable the key */
			pAdapter->SharedKey[BSS0][keyIdx].KeyLen = 0;

		/* Check if the key is not marked as invalid */
		if(!(erq->flags & IW_ENCODE_NOKEY)) {
			/* Copy the key in the driver */
			NdisMoveMemory(pAdapter->SharedKey[BSS0][keyIdx].Key, extra, erq->length);
        }
	}
    else
			{
		/* Do we want to just set the transmit key index ? */
		int index = (erq->flags & IW_ENCODE_INDEX) - 1;
		if ((index >= 0) && (index < 4))
        {
			pAdapter->StaCfg.DefaultKeyId = index;
            }
        else
			/* Don't complain if only change the mode */
			if (!(erq->flags & IW_ENCODE_MODE)) {
				return -EINVAL;
		}
	}

done:
    DBGPRINT(RT_DEBUG_TRACE ,("==>rt_ioctl_siwencode::erq->flags=%x\n",erq->flags));
	DBGPRINT(RT_DEBUG_TRACE ,("==>rt_ioctl_siwencode::AuthMode=%x\n",pAdapter->StaCfg.AuthMode));
	DBGPRINT(RT_DEBUG_TRACE ,("==>rt_ioctl_siwencode::DefaultKeyId=%x, KeyLen = %d\n",pAdapter->StaCfg.DefaultKeyId , pAdapter->SharedKey[BSS0][pAdapter->StaCfg.DefaultKeyId].KeyLen));
	DBGPRINT(RT_DEBUG_TRACE ,("==>rt_ioctl_siwencode::WepStatus=%x\n",pAdapter->StaCfg.WepStatus));
	return 0;
}