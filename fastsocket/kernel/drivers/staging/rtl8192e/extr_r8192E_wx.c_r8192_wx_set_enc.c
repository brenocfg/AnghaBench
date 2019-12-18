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
struct TYPE_2__ {int length; int flags; } ;
union iwreq_data {TYPE_1__ encoding; } ;
typedef  char u8 ;
typedef  char u32 ;
struct r8192_priv {int /*<<< orphan*/  wx_sem; struct ieee80211_device* ieee80211; int /*<<< orphan*/  up; } ;
struct net_device {int dummy; } ;
struct iw_request_info {int dummy; } ;
struct ieee80211_device {char tx_keyidx; void* pairwise_key_type; } ;

/* Variables and functions */
 int /*<<< orphan*/  COMP_SEC ; 
 int ENETDOWN ; 
 int /*<<< orphan*/  EnableHWSecurityConfig8192 (struct net_device*) ; 
 int IW_ENCODE_INDEX ; 
 void* KEY_TYPE_WEP104 ; 
 void* KEY_TYPE_WEP40 ; 
 int /*<<< orphan*/  RT_TRACE (int /*<<< orphan*/ ,char*) ; 
 char* broadcast_addr ; 
 int /*<<< orphan*/  down (int /*<<< orphan*/ *) ; 
 struct r8192_priv* ieee80211_priv (struct net_device*) ; 
 int ieee80211_wx_set_encode (struct ieee80211_device*,struct iw_request_info*,union iwreq_data*,char*) ; 
 int /*<<< orphan*/  printk (char*) ; 
 int read_cam (struct net_device*,char) ; 
 int /*<<< orphan*/  setKey (struct net_device*,int,char,void*,char*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  up (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_cam (struct net_device*,int,int) ; 

__attribute__((used)) static int r8192_wx_set_enc(struct net_device *dev,
			    struct iw_request_info *info,
			    union iwreq_data *wrqu, char *key)
{
	struct r8192_priv *priv = ieee80211_priv(dev);
	int ret;

	struct ieee80211_device *ieee = priv->ieee80211;
	//u32 TargetContent;
	u32 hwkey[4]={0,0,0,0};
	u8 mask=0xff;
	u32 key_idx=0;
	u8 zero_addr[4][6] ={	{0x00,0x00,0x00,0x00,0x00,0x00},
				{0x00,0x00,0x00,0x00,0x00,0x01},
				{0x00,0x00,0x00,0x00,0x00,0x02},
				{0x00,0x00,0x00,0x00,0x00,0x03} };
	int i;

       if(!priv->up) return -ENETDOWN;

	down(&priv->wx_sem);

	RT_TRACE(COMP_SEC, "Setting SW wep key");
	ret = ieee80211_wx_set_encode(priv->ieee80211,info,wrqu,key);

	up(&priv->wx_sem);


	//sometimes, the length is zero while we do not type key value
	if(wrqu->encoding.length!=0){

		for(i=0 ; i<4 ; i++){
			hwkey[i] |=  key[4*i+0]&mask;
			if(i==1&&(4*i+1)==wrqu->encoding.length) mask=0x00;
			if(i==3&&(4*i+1)==wrqu->encoding.length) mask=0x00;
			hwkey[i] |= (key[4*i+1]&mask)<<8;
			hwkey[i] |= (key[4*i+2]&mask)<<16;
			hwkey[i] |= (key[4*i+3]&mask)<<24;
		}

		#define CONF_WEP40  0x4
		#define CONF_WEP104 0x14

		switch(wrqu->encoding.flags & IW_ENCODE_INDEX){
			case 0: key_idx = ieee->tx_keyidx; break;
			case 1:	key_idx = 0; break;
			case 2:	key_idx = 1; break;
			case 3:	key_idx = 2; break;
			case 4:	key_idx	= 3; break;
			default: break;
		}

		//printk("-------====>length:%d, key_idx:%d, flag:%x\n", wrqu->encoding.length, key_idx, wrqu->encoding.flags);
		if(wrqu->encoding.length==0x5){
		ieee->pairwise_key_type = KEY_TYPE_WEP40;
			EnableHWSecurityConfig8192(dev);
			setKey( dev,
				key_idx,                //EntryNo
				key_idx,                //KeyIndex
				KEY_TYPE_WEP40,         //KeyType
				zero_addr[key_idx],
				0,                      //DefaultKey
				hwkey);                 //KeyContent

#if 0
			if(key_idx == 0){

				//write_nic_byte(dev, SECR, 7);
				setKey( dev,
					4,                      //EntryNo
					key_idx,                      //KeyIndex
					KEY_TYPE_WEP40,        //KeyType
					broadcast_addr,         //addr
					0,                      //DefaultKey
					hwkey);                 //KeyContent
			}
#endif
		}

		else if(wrqu->encoding.length==0xd){
			ieee->pairwise_key_type = KEY_TYPE_WEP104;
				EnableHWSecurityConfig8192(dev);
			setKey( dev,
				key_idx,                //EntryNo
				key_idx,                //KeyIndex
				KEY_TYPE_WEP104,        //KeyType
				zero_addr[key_idx],
				0,                      //DefaultKey
				hwkey);                 //KeyContent
#if 0
			if(key_idx == 0){

				//write_nic_byte(dev, SECR, 7);
				setKey( dev,
					4,                      //EntryNo
					key_idx,                      //KeyIndex
					KEY_TYPE_WEP104,        //KeyType
					broadcast_addr,         //addr
					0,                      //DefaultKey
					hwkey);                 //KeyContent
			}
#endif
		}
		else printk("wrong type in WEP, not WEP40 and WEP104\n");


	}

#if 0
	//consider the setting different key index situation
	//wrqu->encoding.flags = 801 means that we set key with index "1"
	if(wrqu->encoding.length==0 && (wrqu->encoding.flags >>8) == 0x8 ){
		printk("===>1\n");
		//write_nic_byte(dev, SECR, 7);
		EnableHWSecurityConfig8192(dev);
		//copy wpa config from default key(key0~key3) to broadcast key(key5)
		//
		key_idx = (wrqu->encoding.flags & 0xf)-1 ;
		write_cam(dev, (4*6),   0xffff0000|read_cam(dev, key_idx*6) );
		write_cam(dev, (4*6)+1, 0xffffffff);
		write_cam(dev, (4*6)+2, read_cam(dev, (key_idx*6)+2) );
		write_cam(dev, (4*6)+3, read_cam(dev, (key_idx*6)+3) );
		write_cam(dev, (4*6)+4, read_cam(dev, (key_idx*6)+4) );
		write_cam(dev, (4*6)+5, read_cam(dev, (key_idx*6)+5) );
	}
#endif

	return ret;
}