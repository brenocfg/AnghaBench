#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct iw_point {int flags; } ;
union iwreq_data {struct iw_point encoding; } ;
typedef  int u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct r8192_priv {int /*<<< orphan*/  wx_sem; struct ieee80211_device* ieee80211; } ;
struct net_device {int dummy; } ;
struct iw_request_info {int dummy; } ;
struct iw_encode_ext {scalar_t__ alg; int ext_flags; int key_len; int /*<<< orphan*/  key; } ;
struct ieee80211_device {int pairwise_key_type; int group_key_type; scalar_t__ iw_mode; int auth_mode; scalar_t__ ap_mac_addr; TYPE_1__* pHTInfo; } ;
struct TYPE_2__ {scalar_t__ bCurrentHTSupport; } ;

/* Variables and functions */
 int /*<<< orphan*/  CamResetAllEntry (struct net_device*) ; 
 int /*<<< orphan*/  EnableHWSecurityConfig8192 (struct net_device*) ; 
 scalar_t__ IW_ENCODE_ALG_CCMP ; 
 scalar_t__ IW_ENCODE_ALG_NONE ; 
 int IW_ENCODE_DISABLED ; 
 int IW_ENCODE_EXT_GROUP_KEY ; 
 int IW_ENCODE_INDEX ; 
 scalar_t__ IW_MODE_ADHOC ; 
 int KEY_TYPE_CCMP ; 
 int KEY_TYPE_NA ; 
 int KEY_TYPE_WEP104 ; 
 int KEY_TYPE_WEP40 ; 
 int /*<<< orphan*/  down (int /*<<< orphan*/ *) ; 
 struct r8192_priv* ieee80211_priv (struct net_device*) ; 
 int ieee80211_wx_set_encode_ext (struct ieee80211_device*,struct iw_request_info*,union iwreq_data*,char*) ; 
 int /*<<< orphan*/  memcpy (int*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  setKey (struct net_device*,int,int,int,int*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  up (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_nic_byte (struct net_device*,int,int) ; 

__attribute__((used)) static int r8192_wx_set_enc_ext(struct net_device *dev,
                                        struct iw_request_info *info,
                                        union iwreq_data *wrqu, char *extra)
{
	int ret=0;
	struct r8192_priv *priv = ieee80211_priv(dev);
	struct ieee80211_device* ieee = priv->ieee80211;

	down(&priv->wx_sem);
	ret = ieee80211_wx_set_encode_ext(ieee, info, wrqu, extra);

	{
		u8 broadcast_addr[6] = {0xff,0xff,0xff,0xff,0xff,0xff};
		u8 zero[6] = {0};
		u32 key[4] = {0};
		struct iw_encode_ext *ext = (struct iw_encode_ext *)extra;
		struct iw_point *encoding = &wrqu->encoding;
#if 0
		static u8 CAM_CONST_ADDR[4][6] = {
			{0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
			{0x00, 0x00, 0x00, 0x00, 0x00, 0x01},
			{0x00, 0x00, 0x00, 0x00, 0x00, 0x02},
			{0x00, 0x00, 0x00, 0x00, 0x00, 0x03}};
#endif
		u8 idx = 0, alg = 0, group = 0;
		if ((encoding->flags & IW_ENCODE_DISABLED) ||
		ext->alg == IW_ENCODE_ALG_NONE) //none is not allowed to use hwsec WB 2008.07.01
		{
			ieee->pairwise_key_type = ieee->group_key_type = KEY_TYPE_NA;
			CamResetAllEntry(dev);
			goto end_hw_sec;
		}
		alg =  (ext->alg == IW_ENCODE_ALG_CCMP)?KEY_TYPE_CCMP:ext->alg; // as IW_ENCODE_ALG_CCMP is defined to be 3 and KEY_TYPE_CCMP is defined to 4;
		idx = encoding->flags & IW_ENCODE_INDEX;
		if (idx)
			idx --;
		group = ext->ext_flags & IW_ENCODE_EXT_GROUP_KEY;

		if ((!group) || (IW_MODE_ADHOC == ieee->iw_mode) || (alg ==  KEY_TYPE_WEP40))
		{
			if ((ext->key_len == 13) && (alg == KEY_TYPE_WEP40) )
				alg = KEY_TYPE_WEP104;
			ieee->pairwise_key_type = alg;
			EnableHWSecurityConfig8192(dev);
		}
		memcpy((u8*)key, ext->key, 16); //we only get 16 bytes key.why? WB 2008.7.1

		if ((alg & KEY_TYPE_WEP40) && (ieee->auth_mode !=2) )
		{
			if (ext->key_len == 13)
				ieee->pairwise_key_type = alg = KEY_TYPE_WEP104;
			setKey( dev,
					idx,//EntryNo
					idx, //KeyIndex
					alg,  //KeyType
					zero, //MacAddr
					0,              //DefaultKey
					key);           //KeyContent
		}
		else if (group)
		{
			ieee->group_key_type = alg;
			setKey( dev,
					idx,//EntryNo
					idx, //KeyIndex
					alg,  //KeyType
					broadcast_addr, //MacAddr
					0,              //DefaultKey
					key);           //KeyContent
		}
		else //pairwise key
		{
			if ((ieee->pairwise_key_type == KEY_TYPE_CCMP) && ieee->pHTInfo->bCurrentHTSupport){
							write_nic_byte(dev, 0x173, 1); //fix aes bug
			}
			setKey( dev,
					4,//EntryNo
					idx, //KeyIndex
					alg,  //KeyType
					(u8*)ieee->ap_mac_addr, //MacAddr
					0,              //DefaultKey
					key);           //KeyContent
		}


	}

end_hw_sec:
	up(&priv->wx_sem);
	return ret;

}