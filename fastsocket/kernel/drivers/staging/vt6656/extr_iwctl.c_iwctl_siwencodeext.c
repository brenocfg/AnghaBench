#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int wpa_alg ;
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_10__ {int alg_name; int set_tx; int key_index; size_t key_len; size_t seq_len; int /*<<< orphan*/ * seq; int /*<<< orphan*/ * key; } ;
struct TYPE_9__ {TYPE_3__ wpa_key; } ;
struct viawget_wpa_param {TYPE_2__ u; int /*<<< orphan*/ * addr; } ;
struct net_device {int dummy; } ;
struct iw_request_info {int dummy; } ;
struct iw_point {int flags; } ;
struct TYPE_8__ {int /*<<< orphan*/ * sa_data; } ;
struct iw_encode_ext {int alg; int ext_flags; size_t key_len; int /*<<< orphan*/ * key; int /*<<< orphan*/ * rx_seq; TYPE_1__ addr; } ;
struct TYPE_11__ {int /*<<< orphan*/ * abyDesireBSSID; } ;
struct TYPE_12__ {scalar_t__ bwextstep3; int /*<<< orphan*/  lock; int /*<<< orphan*/  sKey; scalar_t__ bWPASuppWextEnabled; void* bwextstep2; void* bwextstep1; void* bwextstep0; TYPE_4__ sMgmtObj; } ;
typedef  TYPE_4__* PSMgmtObject ;
typedef  TYPE_5__* PSDevice ;

/* Variables and functions */
 int ENOMEM ; 
 int ETH_ALEN ; 
 void* FALSE ; 
 scalar_t__ GFP_KERNEL ; 
#define  IW_ENCODE_ALG_CCMP 131 
#define  IW_ENCODE_ALG_NONE 130 
#define  IW_ENCODE_ALG_TKIP 129 
#define  IW_ENCODE_ALG_WEP 128 
 int IW_ENCODE_EXT_RX_SEQ_VALID ; 
 int IW_ENCODE_EXT_SET_TX_KEY ; 
 int IW_ENCODE_INDEX ; 
 int IW_ENCODE_SEQ_MAX_SIZE ; 
 int /*<<< orphan*/  KeyvInitTable (TYPE_5__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PRINT_K (char*,...) ; 
 scalar_t__ TRUE ; 
 int WPA_ALG_CCMP ; 
 int WPA_ALG_NONE ; 
 int WPA_ALG_TKIP ; 
 int WPA_ALG_WEP ; 
 size_t ii ; 
 int /*<<< orphan*/  kfree (struct viawget_wpa_param*) ; 
 int /*<<< orphan*/ * kmalloc (int,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  printk (char*,...) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 int wpa_set_keys (TYPE_5__*,struct viawget_wpa_param*,scalar_t__) ; 

int iwctl_siwencodeext(struct net_device *dev,
             struct iw_request_info *info,
             struct iw_point *wrq,
             char *extra)
{
    PSDevice	        pDevice = (PSDevice)netdev_priv(dev);
    PSMgmtObject	pMgmt = &(pDevice->sMgmtObj);
	struct iw_encode_ext *ext = (struct iw_encode_ext*)extra;
    struct viawget_wpa_param *param=NULL;
//original member
    wpa_alg alg_name;
    u8  addr[6];
    int key_idx, set_tx=0;
    u8  seq[IW_ENCODE_SEQ_MAX_SIZE];
    u8 key[64];
    size_t seq_len=0,key_len=0;
//
   // int ii;
    u8 *buf;
    size_t blen;
    u8 key_array[64];
    int ret=0;

PRINT_K("SIOCSIWENCODEEXT...... \n");

blen = sizeof(*param);
buf = kmalloc((int)blen, (int)GFP_KERNEL);
if (buf == NULL)
    return -ENOMEM;
memset(buf, 0, blen);
param = (struct viawget_wpa_param *) buf;

//recover alg_name
switch (ext->alg) {
    case IW_ENCODE_ALG_NONE:
                  alg_name = WPA_ALG_NONE;
		break;
    case IW_ENCODE_ALG_WEP:
                  alg_name = WPA_ALG_WEP;
		break;
    case IW_ENCODE_ALG_TKIP:
                  alg_name = WPA_ALG_TKIP;
		break;
    case IW_ENCODE_ALG_CCMP:
                  alg_name = WPA_ALG_CCMP;
		break;
    default:
		PRINT_K("Unknown alg = %d\n",ext->alg);
		ret= -ENOMEM;
		goto error;
		}
//recover addr
 memcpy(addr, ext->addr.sa_data, ETH_ALEN);
//recover key_idx
  key_idx = (wrq->flags&IW_ENCODE_INDEX) - 1;
//recover set_tx
if(ext->ext_flags & IW_ENCODE_EXT_SET_TX_KEY)
   set_tx = 1;
//recover seq,seq_len
	if(ext->ext_flags & IW_ENCODE_EXT_RX_SEQ_VALID) {
   seq_len=IW_ENCODE_SEQ_MAX_SIZE;
   memcpy(seq, ext->rx_seq, seq_len);
		}
//recover key,key_len
if(ext->key_len) {
  key_len=ext->key_len;
  memcpy(key, &ext->key[0], key_len);
	}

memset(key_array, 0, 64);
if ( key_len > 0) {
     memcpy(key_array, key, key_len);
    if (key_len == 32) {
          // notice ! the oder
	  memcpy(&key_array[16], &key[24], 8);
	  memcpy(&key_array[24], &key[16], 8);
	}
	}

/**************Translate iw_encode_ext to viawget_wpa_param****************/
memcpy(param->addr, addr, ETH_ALEN);
param->u.wpa_key.alg_name = (int)alg_name;
param->u.wpa_key.set_tx = set_tx;
param->u.wpa_key.key_index = key_idx;
param->u.wpa_key.key_len = key_len;
param->u.wpa_key.key = (u8 *)key_array;
param->u.wpa_key.seq = (u8 *)seq;
param->u.wpa_key.seq_len = seq_len;

#if 0
printk("param->u.wpa_key.alg_name =%d\n",param->u.wpa_key.alg_name);
printk("param->addr=%02x:%02x:%02x:%02x:%02x:%02x\n",
	      param->addr[0],param->addr[1],param->addr[2],
	      param->addr[3],param->addr[4],param->addr[5]);
printk("param->u.wpa_key.set_tx =%d\n",param->u.wpa_key.set_tx);
printk("param->u.wpa_key.key_index =%d\n",param->u.wpa_key.key_index);
printk("param->u.wpa_key.key_len =%d\n",param->u.wpa_key.key_len);
printk("param->u.wpa_key.key =");
for(ii=0;ii<param->u.wpa_key.key_len;ii++)
	printk("%02x:",param->u.wpa_key.key[ii]);
         printk("\n");
printk("param->u.wpa_key.seq_len =%d\n",param->u.wpa_key.seq_len);
printk("param->u.wpa_key.seq =");
for(ii=0;ii<param->u.wpa_key.seq_len;ii++)
	printk("%02x:",param->u.wpa_key.seq[ii]);
         printk("\n");

printk("...........\n");
#endif
//****set if current action is Network Manager count??
//****this method is so foolish,but there is no other way???
if(param->u.wpa_key.alg_name == WPA_ALG_NONE) {
   if(param->u.wpa_key.key_index ==0) {
     pDevice->bwextstep0 = TRUE;
    }
   if((pDevice->bwextstep0 = TRUE)&&(param->u.wpa_key.key_index ==1)) {
     pDevice->bwextstep0 = FALSE;
     pDevice->bwextstep1 = TRUE;
    }
   if((pDevice->bwextstep1 = TRUE)&&(param->u.wpa_key.key_index ==2)) {
     pDevice->bwextstep1 = FALSE;
     pDevice->bwextstep2 = TRUE;
	}
   if((pDevice->bwextstep2 = TRUE)&&(param->u.wpa_key.key_index ==3)) {
     pDevice->bwextstep2 = FALSE;
     pDevice->bwextstep3 = TRUE;
        }
		 }
if(pDevice->bwextstep3 == TRUE) {
    PRINT_K("SIOCSIWENCODEEXT:Enable WPA WEXT SUPPORT!!!!!\n");
     pDevice->bwextstep0 = FALSE;
     pDevice->bwextstep1 = FALSE;
     pDevice->bwextstep2 = FALSE;
     pDevice->bwextstep3 = FALSE;
     pDevice->bWPASuppWextEnabled = TRUE;
     memset(pMgmt->abyDesireBSSID, 0xFF,6);
     KeyvInitTable(pDevice,&pDevice->sKey);
		 }
//******

		spin_lock_irq(&pDevice->lock);
 ret = wpa_set_keys(pDevice, param, TRUE);
		spin_unlock_irq(&pDevice->lock);

error:
kfree(param);
	return ret;
}