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
typedef  int /*<<< orphan*/  u32_t ;
typedef  int /*<<< orphan*/  u16_t ;
struct zsHpPriv {int halReInit; scalar_t__ usbRxTransferLen; scalar_t__ usbRxPadLen; scalar_t__ usbRxPktLen; scalar_t__ usbRxRemainLen; int /*<<< orphan*/ * remainBuf; scalar_t__ rxStrongRSSI; scalar_t__ strongRSSI; } ;
struct TYPE_2__ {scalar_t__ hpPrivate; } ;

/* Variables and functions */
 int /*<<< orphan*/  ZM_FIRMWARE_WLAN_ADDR ; 
 int /*<<< orphan*/  ZM_SUCCESS ; 
 TYPE_1__* wd ; 
 scalar_t__ zcFwImage ; 
 scalar_t__ zcFwImageSize ; 
 scalar_t__ zcP2FwImage ; 
 scalar_t__ zcP2FwImageSize ; 
 int /*<<< orphan*/  zfCoreReinit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zfFirmwareDownload (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zfHpEchoCommand (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  zfHpUsbReset (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zfInitCmdQueue (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zfInitMac (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zfInitPhy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zfInitRf (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zfInitUsbMode (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zfwBufFree (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zmw_get_wlan_dev (int /*<<< orphan*/ *) ; 

u16_t zfHpReinit(zdev_t* dev, u32_t frequency)
{
    u16_t ret;
    zmw_get_wlan_dev(dev);

    ((struct zsHpPriv*)wd->hpPrivate)->halReInit = 1;

    ((struct zsHpPriv*)wd->hpPrivate)->strongRSSI = 0;
    ((struct zsHpPriv*)wd->hpPrivate)->rxStrongRSSI = 0;

#ifdef ZM_OTUS_RX_STREAM_MODE
    if (((struct zsHpPriv*)wd->hpPrivate)->remainBuf != NULL)
    {
        zfwBufFree(dev, ((struct zsHpPriv*)wd->hpPrivate)->remainBuf, 0);
    }
    ((struct zsHpPriv*)wd->hpPrivate)->remainBuf = NULL;
    ((struct zsHpPriv*)wd->hpPrivate)->usbRxRemainLen = 0;
    ((struct zsHpPriv*)wd->hpPrivate)->usbRxPktLen = 0;
    ((struct zsHpPriv*)wd->hpPrivate)->usbRxPadLen = 0;
    ((struct zsHpPriv*)wd->hpPrivate)->usbRxTransferLen = 0;
#endif

    zfInitCmdQueue(dev);
    zfCoreReinit(dev);

    #ifndef ZM_OTUS_LINUX_PHASE_2
    /* Download firmware */
    if ((ret = zfFirmwareDownload(dev, (u32_t*)zcFwImage,
            (u32_t)zcFwImageSize, ZM_FIRMWARE_WLAN_ADDR)) != ZM_SUCCESS)
    {
        /* TODO : exception handling */
        //return 1;
    }
    #else
    if ((ret = zfFirmwareDownload(dev, (u32_t*)zcP2FwImage,
            (u32_t)zcP2FwImageSize, ZM_FIRMWARE_WLAN_ADDR)) != ZM_SUCCESS)
    {
        /* TODO : exception handling */
        //return 1;
    }
    #endif

#ifdef ZM_DRV_INIT_USB_MODE
    /* Init USB Mode */
    zfInitUsbMode(dev);

    /* Do the USB Reset */
    zfHpUsbReset(dev);
#endif

    /* Init MAC */
    zfInitMac(dev);

    /* Init PHY */
    zfInitPhy(dev, frequency, 0);
    /* Init RF */
    zfInitRf(dev, frequency);

    #if ZM_FPGA_PHY == 0
    /* BringUp issue */
    //zfDelayWriteInternalReg(dev, 0x9800+0x1bc000, 0x10000007);
    //zfFlushDelayWrite(dev);
    #endif

    zfHpEchoCommand(dev, 0xAABBCCDD);

    return 0;
}