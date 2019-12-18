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
typedef  int /*<<< orphan*/  zdev_t ;
typedef  int /*<<< orphan*/  zbuf_t ;
typedef  int u16_t ;
struct aggBaFrameParameter {int ba_parameter; int ba_policy; int tid; int buffer_size; void* ba_timeout; void* status_code; int /*<<< orphan*/  dialog; int /*<<< orphan*/ * buf; } ;
struct TYPE_2__ {scalar_t__ wlanMode; int addbaComplete; } ;

/* Variables and functions */
 scalar_t__ ZM_MODE_AP ; 
 int ZM_SUCCESS ; 
 TYPE_1__* wd ; 
 int* zcUpToAc ; 
 int zfApFindSta (int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  zm_debug_msg2 (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zmw_get_wlan_dev (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zmw_rx_buf_readb (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 void* zmw_rx_buf_readh (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

u16_t   zfAggRecvAddbaResponse(zdev_t* dev, zbuf_t* buf)
{
    u16_t i,ac, aid=0;
    u16_t src[3];
    struct aggBaFrameParameter bf;

    zmw_get_wlan_dev(dev);

    //zmw_declare_for_critical_section();

    src[0] = zmw_rx_buf_readh(dev, buf, 10);
    src[1] = zmw_rx_buf_readh(dev, buf, 12);
    src[2] = zmw_rx_buf_readh(dev, buf, 14);

    if (wd->wlanMode == ZM_MODE_AP)
        aid = zfApFindSta(dev, src);


    bf.buf = buf;
    bf.dialog = zmw_rx_buf_readb(dev, buf, 26);
    bf.status_code = zmw_rx_buf_readh(dev, buf, 27);
    if (!bf.status_code)
    {
        wd->addbaComplete=1;
    }

    /*
     * ba parameter set
     */
    bf.ba_parameter = zmw_rx_buf_readh(dev, buf, 29);
    bf.ba_policy   = (bf.ba_parameter >> 1) & 1;
    bf.tid         = (bf.ba_parameter >> 2) & 0xF;
    bf.buffer_size = (bf.ba_parameter >> 6);
    /*
     * BA timeout value
     */
    bf.ba_timeout = zmw_rx_buf_readh(dev, buf, 31);

    i=26;
    while(i < 32) {
        zm_debug_msg2("Recv ADDBA Rsp:", zmw_rx_buf_readb(dev,buf,i));
        i++;
    }

    ac = zcUpToAc[bf.tid&0x7] & 0x3;

    //zmw_enter_critical_section(dev);

    //wd->aggSta[aid].aggFlag[ac] = 0;

    //zmw_leave_critical_section(dev);

    return ZM_SUCCESS;
}