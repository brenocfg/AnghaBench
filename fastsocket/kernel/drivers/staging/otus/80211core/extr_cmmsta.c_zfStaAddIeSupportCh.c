#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zdev_t ;
typedef  int /*<<< orphan*/  zbuf_t ;
typedef  size_t u8_t ;
typedef  int u16_t ;
struct TYPE_5__ {size_t allowChannelCnt; TYPE_1__* allowChannel; } ;
struct TYPE_6__ {TYPE_2__ regulationTable; } ;
struct TYPE_4__ {int channel; } ;

/* Variables and functions */
 size_t ZM_WLAN_EID_SUPPORTED_CHANNELS ; 
 TYPE_3__* wd ; 
 int /*<<< orphan*/  zmw_declare_for_critical_section () ; 
 int /*<<< orphan*/  zmw_enter_critical_section (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zmw_get_wlan_dev (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zmw_leave_critical_section (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zmw_tx_buf_writeb (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  zmw_tx_buf_writeh (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

u16_t zfStaAddIeSupportCh(zdev_t* dev, zbuf_t* buf, u16_t offset)
{

    u8_t   i;
    u16_t  count_24G = 0;
    u16_t  count_5G = 0;
    u16_t  channelNum;
    u8_t   length;

    zmw_get_wlan_dev(dev);

    zmw_declare_for_critical_section();
    zmw_enter_critical_section(dev);

    for (i = 0; i < wd->regulationTable.allowChannelCnt; i++)
    {
        if (wd->regulationTable.allowChannel[i].channel < 3000)
        { // 2.4Hz
            count_24G++;
        }
        else
        { // 5GHz
            count_5G++;
        }
    }

    length = (u8_t)(count_5G * 2 + 2); //5G fill by pair, 2,4G (continuous channels) fill 2 bytes

    /* Element ID */
    zmw_tx_buf_writeb(dev, buf, offset++, ZM_WLAN_EID_SUPPORTED_CHANNELS );

    /* Element Length */
    zmw_tx_buf_writeb(dev, buf, offset++, length);

    // 2.4GHz (continuous channels)
    /* First channel number */
    zmw_tx_buf_writeh(dev, buf, offset++, 1); //Start from channle 1
    /* Number of channels */
    zmw_tx_buf_writeh(dev, buf, offset++, count_24G);

    for (i = 0; i < wd->regulationTable.allowChannelCnt ; i++)
    {
        if (wd->regulationTable.allowChannel[i].channel > 4000 && wd->regulationTable.allowChannel[i].channel < 5000)
        { // 5GHz 4000 -5000Mhz
            channelNum = (wd->regulationTable.allowChannel[i].channel-4000)/5;
            /* First channel number */
            zmw_tx_buf_writeh(dev, buf, offset++, channelNum);
            /* Number of channels */
            zmw_tx_buf_writeh(dev, buf, offset++, 1);
        }
        else if (wd->regulationTable.allowChannel[i].channel >= 5000)
        { // 5GHz >5000Mhz
            channelNum = (wd->regulationTable.allowChannel[i].channel-5000)/5;
            /* First channel number */
            zmw_tx_buf_writeh(dev, buf, offset++, channelNum);
            /* Number of channels */
            zmw_tx_buf_writeh(dev, buf, offset++, 1);
        }
    }
   zmw_leave_critical_section(dev);

    return offset;
}