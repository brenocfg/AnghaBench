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
typedef  int /*<<< orphan*/  zdev_t ;
typedef  int /*<<< orphan*/  zbuf_t ;
typedef  int /*<<< orphan*/  u8_t ;
typedef  int u32_t ;
typedef  int u16_t ;
struct agg_tid_rx {int dummy; } ;
struct TYPE_3__ {scalar_t__ EnableHT; } ;
struct TYPE_4__ {TYPE_1__ sta; } ;

/* Variables and functions */
 int /*<<< orphan*/  ZM_SEQ_DEBUG (char*,int,int) ; 
 int ZM_WLAN_DATA_FRAME ; 
 TYPE_2__* wd ; 
 struct agg_tid_rx* zfAggRxGetQueue (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int zfApFindSta (int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  zmw_get_wlan_dev (int /*<<< orphan*/ *) ; 
 int zmw_rx_buf_readb (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int zmw_rx_buf_readh (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

struct agg_tid_rx* zfAggRxEnabled(zdev_t* dev, zbuf_t* buf)
{
    u16_t   dst0, src[3], ac, aid, fragOff;
    u8_t    up;
    u16_t   offset = 0;
    u16_t   seq_no;
    u16_t frameType;
    u16_t frameCtrl;
    u16_t frameSubtype;
    u32_t tcp_seq;
    //struct aggSta *agg_sta;
#if ZM_AGG_FPGA_REORDERING
    struct agg_tid_rx *tid_rx;
#endif
    zmw_get_wlan_dev(dev);

    //zmw_declare_for_critical_section();
    seq_no = zmw_rx_buf_readh(dev, buf, 22) >> 4;
    //DbgPrint("Rx seq=%d\n", seq_no);
    if (wd->sta.EnableHT == 0)
    {
        return NULL;
    }

    frameCtrl = zmw_rx_buf_readb(dev, buf, 0);
    frameType = frameCtrl & 0xf;
    frameSubtype = frameCtrl & 0xf0;


    if (frameType != ZM_WLAN_DATA_FRAME) //non-Qos Data? (frameSubtype&0x80)
    {
        return NULL;
    }
#ifdef ZM_ENABLE_PERFORMANCE_EVALUATION
    tcp_seq = zmw_rx_buf_readb(dev, buf, 22+36) << 24;
    tcp_seq += zmw_rx_buf_readb(dev, buf, 22+37) << 16;
    tcp_seq += zmw_rx_buf_readb(dev, buf, 22+38) << 8;
    tcp_seq += zmw_rx_buf_readb(dev, buf, 22+39);
#endif

    ZM_SEQ_DEBUG("In                   %5d, %12u\n", seq_no, tcp_seq);
    dst0 = zmw_rx_buf_readh(dev, buf, offset+4);

    src[0] = zmw_rx_buf_readh(dev, buf, offset+10);
    src[1] = zmw_rx_buf_readh(dev, buf, offset+12);
    src[2] = zmw_rx_buf_readh(dev, buf, offset+14);

#if ZM_AGG_FPGA_DEBUG
    aid = 0;
#else
    aid = zfApFindSta(dev, src);
#endif

    //agg_sta = &wd->aggSta[aid];
    //zfTxGetIpTosAndFrag(dev, buf, &up, &fragOff);
    //ac = zcUpToAc[up&0x7] & 0x3;

    /*
     * Filter unicast frame only, aid == 0 is for debug only
     */
    if ((dst0 & 0x1) == 0 && aid == 0)
    {
#if ZM_AGG_FPGA_REORDERING
        tid_rx = zfAggRxGetQueue(dev, buf) ;
        if(!tid_rx)
            return NULL;
        else
        {
            //if (tid_rx->addBaExchangeStatusCode == ZM_AGG_ADDBA_RESPONSE)
            return tid_rx;
        }
#else
        return NULL;
#endif
    }

    return NULL;
}