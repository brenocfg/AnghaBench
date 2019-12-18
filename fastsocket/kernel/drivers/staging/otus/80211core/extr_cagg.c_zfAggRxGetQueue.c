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
typedef  size_t u16_t ;
struct agg_tid_rx {size_t aid; size_t ac; } ;
struct TYPE_2__ {struct agg_tid_rx** tid_rx; } ;

/* Variables and functions */
 size_t ZM_AGG_POOL_SIZE ; 
 TYPE_1__* wd ; 
 size_t zfApFindSta (int /*<<< orphan*/ *,size_t*) ; 
 int /*<<< orphan*/  zmw_get_wlan_dev (int /*<<< orphan*/ *) ; 
 int zmw_rx_buf_readh (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

struct agg_tid_rx *zfAggRxGetQueue(zdev_t* dev, zbuf_t* buf)
{
    u16_t   src[3];
    u16_t   aid, ac, i;
    u16_t   offset = 0;
    struct agg_tid_rx *tid_rx = NULL;

    zmw_get_wlan_dev(dev);

    //zmw_declare_for_critical_section();

    src[0] = zmw_rx_buf_readh(dev, buf, offset+10);
    src[1] = zmw_rx_buf_readh(dev, buf, offset+12);
    src[2] = zmw_rx_buf_readh(dev, buf, offset+14);
    aid = zfApFindSta(dev, src);

    ac = (zmw_rx_buf_readh(dev, buf, 24) & 0xF);

    // mark by spin lock debug
    //zmw_enter_critical_section(dev);

    for (i=0; i<ZM_AGG_POOL_SIZE ; i++)
    {
        if((wd->tid_rx[i]->aid == aid) && (wd->tid_rx[i]->ac == ac))
        {
            tid_rx = wd->tid_rx[i];
            break;
        }
    }

    // mark by spin lock debug
    //zmw_leave_critical_section(dev);
    return tid_rx;
}