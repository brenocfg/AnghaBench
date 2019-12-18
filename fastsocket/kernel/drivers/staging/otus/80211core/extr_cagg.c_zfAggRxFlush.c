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
typedef  int u16_t ;
struct zsAdditionInfo {int dummy; } ;
struct agg_tid_rx {size_t baw_tail; size_t baw_head; int seq_start; TYPE_1__* frame; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* zfcbRecv80211 ) (int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct zsAdditionInfo*) ;} ;
struct TYPE_3__ {int /*<<< orphan*/ * buf; int /*<<< orphan*/  addInfo; } ;

/* Variables and functions */
 int ZM_AGG_BAW_MASK ; 
 int /*<<< orphan*/  ZM_PERFORMANCE_RX_FLUSH (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ZM_PERFORMANCE_RX_SEQ (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct zsAdditionInfo*) ; 
 TYPE_2__* wd ; 
 int /*<<< orphan*/  zfiRecv80211 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct zsAdditionInfo*) ; 
 int /*<<< orphan*/  zfwMemoryCopy (void*,void*,int) ; 
 int /*<<< orphan*/  zmw_declare_for_critical_section () ; 
 int /*<<< orphan*/  zmw_enter_critical_section (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zmw_get_wlan_dev (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zmw_leave_critical_section (int /*<<< orphan*/ *) ; 
 int zmw_rx_buf_readh (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

u16_t zfAggRxFlush(zdev_t* dev, u16_t seq_no, struct agg_tid_rx *tid_rx)
{
    zbuf_t* pbuf;
    u16_t   seq;
    struct zsAdditionInfo addInfo;
    zmw_get_wlan_dev(dev);
    zmw_declare_for_critical_section();

    ZM_PERFORMANCE_RX_FLUSH(dev);

    while (1)
    {
        zmw_enter_critical_section(dev);
        if (tid_rx->baw_tail == tid_rx->baw_head) {
            zmw_leave_critical_section(dev);
            break;
        }

        pbuf = tid_rx->frame[tid_rx->baw_tail].buf;
        zfwMemoryCopy((void*)&addInfo, (void*)&tid_rx->frame[tid_rx->baw_tail].addInfo, sizeof(struct zsAdditionInfo));
        tid_rx->frame[tid_rx->baw_tail].buf = 0;
        //if(pbuf && tid_rx->baw_size > 0) tid_rx->baw_size--;
        tid_rx->baw_tail = (tid_rx->baw_tail + 1) & ZM_AGG_BAW_MASK;
        tid_rx->seq_start = (tid_rx->seq_start + 1) & (4096 - 1);
	    zmw_leave_critical_section(dev);

        if (pbuf)
        {

            ZM_PERFORMANCE_RX_SEQ(dev, pbuf);

            if (wd->zfcbRecv80211 != NULL)
            {
                seq = zmw_rx_buf_readh(dev, pbuf, 22) >> 4;
                //DbgPrint("Recv indicate seq=%d\n", seq);
                //DbgPrint("2. seq=%d\n", seq);
                wd->zfcbRecv80211(dev, pbuf, &addInfo);
            }
            else
            {
                seq = zmw_rx_buf_readh(dev, pbuf, 22) >> 4;
                //DbgPrint("Recv indicate seq=%d\n", seq);
                zfiRecv80211(dev, pbuf, &addInfo);
            }
        }
    }

    zmw_enter_critical_section(dev);
    tid_rx->baw_head = tid_rx->baw_tail = 0;
    zmw_leave_critical_section(dev);
    return 1;
}