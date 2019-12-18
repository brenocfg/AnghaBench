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
typedef  int u8_t ;
typedef  int u32_t ;
typedef  int u16_t ;
struct zsHpPriv {int retransmissionEvent; } ;
struct TYPE_2__ {struct zsHpPriv* hpPrivate; int /*<<< orphan*/  (* zfcbHwWatchDogNotify ) (int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  DbgPrint (char*,int,...) ; 
 int /*<<< orphan*/  ZM_LV_3 ; 
#define  ZM_STATUS_RETRY_COMP 130 
#define  ZM_STATUS_TX_COMP 129 
#define  ZM_STATUS_TX_FAILED 128 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *) ; 
 TYPE_1__* wd ; 
 int /*<<< orphan*/  zfBeaconCfgInterrupt (int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  zfCoreEvent (int /*<<< orphan*/ *,int,int*) ; 
 int /*<<< orphan*/  zfEndOfAtimWindowInterrupt (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zfIdlRsp (int /*<<< orphan*/ *,int*,int) ; 
 int /*<<< orphan*/  zfwDbgProgrameFlashChkDone (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zm_debug_msg0 (char*) ; 
 int /*<<< orphan*/  zm_msg0_mm (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  zmw_get_wlan_dev (int /*<<< orphan*/ *) ; 

void zfiUsbRegIn(zdev_t* dev, u32_t* rsp, u16_t rspLen)
{
    //u8_t len, type, i;
    u8_t type;
    u8_t *u8rsp;
    u16_t status;
    u32_t bitmap;
    zmw_get_wlan_dev(dev);

    zm_msg0_mm(ZM_LV_3, "zfiUsbRegIn()");

    u8rsp = (u8_t *)rsp;

    //len = *u8rsp;
    type = *(u8rsp+1);
    u8rsp = u8rsp+4;


    /* Interrupt event */
    if ((type & 0xC0) == 0xC0)
    {
        if (type == 0xC0)
        {
            zfCoreEvent(dev, 0, u8rsp);

        }
        else if (type == 0xC1)
        {
#if 0
            {
                u16_t i;
                DbgPrint("rspLen=%d\n", rspLen);
                for (i=0; i<(rspLen/4); i++)
                {
                    DbgPrint("rsp[%d]=0x%lx\n", i, rsp[i]);
                }
            }
#endif
            status = (u16_t)(rsp[3] >> 16);

            ////6789
            rsp[8] = rsp[8] >> 2 | (rsp[9] & 0x1) << 6;
            switch (status)
            {
            case ZM_STATUS_RETRY_COMP :
                zfCoreEvent(dev, 1, u8rsp);
                break;
            case ZM_STATUS_TX_FAILED :
                zfCoreEvent(dev, 2, u8rsp);
                break;
            case ZM_STATUS_TX_COMP :
                zfCoreEvent(dev, 3, u8rsp);
                break;
            }
        }
        else if (type == 0xC2)
        {
            zfBeaconCfgInterrupt(dev, u8rsp);
        }
        else if (type == 0xC3)
        {
            zfEndOfAtimWindowInterrupt(dev);
        }
        else if (type == 0xC4)
        {
#if 0
            {
                u16_t i;
                DbgPrint("0xC2:rspLen=%d\n", rspLen);
                for (i=0; i<(rspLen/4); i++)
                {
                    DbgPrint("0xC2:rsp[%d]=0x%lx\n", i, rsp[i]);
                }
            }
#endif
            bitmap = (rsp[1] >> 16) + ((rsp[2] & 0xFFFF) << 16 );
            //zfBawCore(dev, (u16_t)rsp[1] & 0xFFFF, bitmap, (u16_t)(rsp[2] >> 16) & 0xFF);
        }
        else if (type == 0xC5)
        {
            u16_t i;
#if 0

            for (i=0; i<(rspLen/4); i++) {
                DbgPrint("0xC5:rsp[%d]=0x%lx\n", i, rsp[i]);
            }
#endif
            for (i=1; i<(rspLen/4); i++) {
                u8rsp = (u8_t *)(rsp+i);
                //DbgPrint("0xC5:rsp[%d]=0x%lx\n", i, ((u32_t*)u8rsp)[0]);
                zfCoreEvent(dev, 4, u8rsp);
            }
        }
        else if (type == 0xC6)
        {
            zm_debug_msg0("\n\n WatchDog interrupt!!! : 0xC6 \n\n");
            if (wd->zfcbHwWatchDogNotify != NULL)
            {
                wd->zfcbHwWatchDogNotify(dev);
            }
        }
        else if (type == 0xC8)
        {
            //PZSW_ADAPTER adapter;

            // for SPI flash program chk Flag
            zfwDbgProgrameFlashChkDone(dev);
        }
        else if (type == 0xC9)
        {
            struct zsHpPriv* hpPriv=wd->hpPrivate;

            zm_debug_msg0("##### Tx retransmission 5 times event #####");

            /* correct tx retransmission issue */
            hpPriv->retransmissionEvent = 1;
        }
    }
    else
    {
        zfIdlRsp(dev, rsp, rspLen);
    }
}