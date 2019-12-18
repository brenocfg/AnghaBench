#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_7__ ;
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
struct TYPE_16__ {void* last_rx; struct usbdrv_private* ml_priv; } ;
typedef  TYPE_3__ zdev_t ;
struct TYPE_17__ {scalar_t__ len; void* ip_summed; void* protocol; TYPE_3__* dev; scalar_t__ data; scalar_t__ tail; } ;
typedef  TYPE_4__ zbuf_t ;
typedef  scalar_t__ u16_t ;
struct TYPE_14__ {scalar_t__ rx_bytes; int /*<<< orphan*/  rx_packets; } ;
struct TYPE_15__ {TYPE_1__ net_stats; } ;
struct usbdrv_private {TYPE_2__ drv_stats; } ;
struct TYPE_18__ {TYPE_3__* dev; } ;

/* Variables and functions */
 void* CHECKSUM_NONE ; 
#define  NET_RX_DROP 128 
 TYPE_4__* dev_alloc_skb (scalar_t__) ; 
 int /*<<< orphan*/  dev_kfree_skb_any (TYPE_4__*) ; 
 void* eth_type_trans (TYPE_4__*,TYPE_3__*) ; 
 void* jiffies ; 
 int /*<<< orphan*/  memcpy (scalar_t__,scalar_t__,scalar_t__) ; 
 int netif_rx (TYPE_4__*) ; 
 int /*<<< orphan*/  skb_put (TYPE_4__*,scalar_t__) ; 
 TYPE_7__* vap ; 

void zfLnxRecvEth(zdev_t* dev, zbuf_t* buf, u16_t port)
{
    struct usbdrv_private *macp = dev->ml_priv;
#ifdef ZM_AVOID_UDP_LARGE_PACKET_FAIL
    zbuf_t *new_buf;

    //new_buf = dev_alloc_skb(2048);
    new_buf = dev_alloc_skb(buf->len);

#ifdef NET_SKBUFF_DATA_USES_OFFSET
    new_buf->tail = 0;
    new_buf->len = 0;
#else
    new_buf->tail = new_buf->data;
    new_buf->len = 0;
#endif

    skb_put(new_buf, buf->len);
    memcpy(new_buf->data, buf->data, buf->len);

    /* Free buffer */
    dev_kfree_skb_any(buf);

    if (port == 0)
    {
        new_buf->dev = dev;
        new_buf->protocol = eth_type_trans(new_buf, dev);
    }
    else
    {
        /* VAP */
        if (vap[0].dev != NULL)
        {
            new_buf->dev = vap[0].dev;
            new_buf->protocol = eth_type_trans(new_buf, vap[0].dev);
        }
        else
        {
            new_buf->dev = dev;
            new_buf->protocol = eth_type_trans(new_buf, dev);
        }
    }

    new_buf->ip_summed = CHECKSUM_NONE;
    dev->last_rx = jiffies;

    switch(netif_rx(new_buf))
#else
    if (port == 0)
    {
        buf->dev = dev;
        buf->protocol = eth_type_trans(buf, dev);
    }
    else
    {
        /* VAP */
        if (vap[0].dev != NULL)
        {
            buf->dev = vap[0].dev;
            buf->protocol = eth_type_trans(buf, vap[0].dev);
        }
        else
        {
            buf->dev = dev;
            buf->protocol = eth_type_trans(buf, dev);
        }
    }

    buf->ip_summed = CHECKSUM_NONE;
    dev->last_rx = jiffies;

    switch(netif_rx(buf))
#endif
    {
    case NET_RX_DROP:
        break;
    default:
            macp->drv_stats.net_stats.rx_packets++;
            macp->drv_stats.net_stats.rx_bytes += buf->len;
        break;
    }

    return;
}