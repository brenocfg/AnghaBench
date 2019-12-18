#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {struct usbdrv_private* ml_priv; } ;
typedef  TYPE_1__ zdev_t ;
struct TYPE_11__ {int /*<<< orphan*/  protocol; int /*<<< orphan*/  pkt_type; int /*<<< orphan*/  ip_summed; scalar_t__ data; scalar_t__ mac_header; TYPE_1__* dev; } ;
typedef  TYPE_2__ zbuf_t ;
typedef  int u8_t ;
typedef  int u16_t ;
struct zsAdditionInfo {int dummy; } ;
struct usbdrv_private {scalar_t__ forwardMgmt; } ;

/* Variables and functions */
 int /*<<< orphan*/  CHECKSUM_NONE ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  PACKET_OTHERHOST ; 
 int /*<<< orphan*/  __constant_htons (int) ; 
 int /*<<< orphan*/  netif_rx (TYPE_2__*) ; 
 TYPE_2__* skb_copy (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zfiRecv80211 (TYPE_1__*,TYPE_2__*,struct zsAdditionInfo*) ; 

void zfLnxRecv80211(zdev_t* dev, zbuf_t* buf, struct zsAdditionInfo* addInfo)
{
    u16_t frameType;
    u16_t frameCtrl;
    u16_t frameSubtype;
    zbuf_t *skb1;
    struct usbdrv_private *macp = dev->ml_priv;

    //frameCtrl = zmw_buf_readb(dev, buf, 0);
    frameCtrl = *(u8_t*)((u8_t*)buf->data);
    frameType = frameCtrl & 0xf;
    frameSubtype = frameCtrl & 0xf0;

    if ((frameType == 0x0) && (macp->forwardMgmt))
    {
        switch (frameSubtype)
        {
                /* Beacon */
            case 0x80 :
                /* Probe response */
            case 0x50 :
                skb1 = skb_copy(buf, GFP_ATOMIC);
                if(skb1 != NULL)
                {
                    skb1->dev = dev;
                    skb1->mac_header = skb1->data;
	            skb1->ip_summed = CHECKSUM_NONE;
	            skb1->pkt_type = PACKET_OTHERHOST;
	            skb1->protocol = __constant_htons(0x0019);  /* ETH_P_80211_RAW */
    	            netif_rx(skb1);
	            }
                break;
            default:
                break;
        }
    }

    zfiRecv80211(dev, buf, addInfo);
    return;
}