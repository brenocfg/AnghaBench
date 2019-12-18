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
struct zsHpPriv {int* ledMode; int slotType; int aggPktNum; int enableBBHeavyClip; int hwBBHeavyClip; scalar_t__ setValueHeavyClip; scalar_t__ doBBHeavyClip; scalar_t__ usbRxTransferLen; scalar_t__ usbRxPadLen; scalar_t__ usbRxPktLen; scalar_t__ usbRxRemainLen; int /*<<< orphan*/ * remainBuf; scalar_t__ eepromImageRdReq; scalar_t__ eepromImageIndex; scalar_t__ rxStrongRSSI; scalar_t__ strongRSSI; scalar_t__ disableDfsCh; scalar_t__ hwExtOffset; scalar_t__ hwBw40; scalar_t__ hwFrequency; int /*<<< orphan*/  halCapability; } ;
struct TYPE_2__ {scalar_t__ modeMDKEnable; int /*<<< orphan*/ * hpPrivate; } ;

/* Variables and functions */
 int /*<<< orphan*/  DbgPrint (char*) ; 
 int /*<<< orphan*/  ZM_FIRMWARE_WLAN_ADDR ; 
 int /*<<< orphan*/  ZM_HP_CAP_11N ; 
 int /*<<< orphan*/  ZM_SUCCESS ; 
 TYPE_1__* wd ; 
 scalar_t__ zcDKFwImage ; 
 scalar_t__ zcDKFwImageSize ; 
 scalar_t__ zcFwBufImage ; 
 scalar_t__ zcFwBufImageSize ; 
 scalar_t__ zcFwImage ; 
 scalar_t__ zcFwImageSize ; 
 int /*<<< orphan*/  zfFirmwareDownload (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zfFirmwareDownloadNotJump (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  zfHpEchoCommand (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  zfHpUsbReset (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zfInitCmdQueue (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zfInitMac (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zfInitPhy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zfInitRf (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zfInitUsbMode (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zfUsbInit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zfwSleep (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  zgHpPriv ; 
 int /*<<< orphan*/  zmw_get_wlan_dev (int /*<<< orphan*/ *) ; 

u16_t zfHpInit(zdev_t* dev, u32_t frequency)
{
    u16_t ret;
    zmw_get_wlan_dev(dev);

    /* Initializa HAL Plus private variables */
    wd->hpPrivate = &zgHpPriv;

    ((struct zsHpPriv*)wd->hpPrivate)->halCapability = ZM_HP_CAP_11N;

    ((struct zsHpPriv*)wd->hpPrivate)->hwFrequency = 0;
    ((struct zsHpPriv*)wd->hpPrivate)->hwBw40 = 0;
    ((struct zsHpPriv*)wd->hpPrivate)->hwExtOffset = 0;

    ((struct zsHpPriv*)wd->hpPrivate)->disableDfsCh = 0;

    ((struct zsHpPriv*)wd->hpPrivate)->ledMode[0] = 1;
    ((struct zsHpPriv*)wd->hpPrivate)->ledMode[1] = 1;
    ((struct zsHpPriv*)wd->hpPrivate)->strongRSSI = 0;
    ((struct zsHpPriv*)wd->hpPrivate)->rxStrongRSSI = 0;

    ((struct zsHpPriv*)wd->hpPrivate)->slotType = 1;
    ((struct zsHpPriv*)wd->hpPrivate)->aggPktNum = 0x10000a;

    ((struct zsHpPriv*)wd->hpPrivate)->eepromImageIndex = 0;


    ((struct zsHpPriv*)wd->hpPrivate)->eepromImageRdReq     = 0;
#ifdef ZM_OTUS_RX_STREAM_MODE
    ((struct zsHpPriv*)wd->hpPrivate)->remainBuf = NULL;
    ((struct zsHpPriv*)wd->hpPrivate)->usbRxRemainLen = 0;
    ((struct zsHpPriv*)wd->hpPrivate)->usbRxPktLen = 0;
    ((struct zsHpPriv*)wd->hpPrivate)->usbRxPadLen = 0;
    ((struct zsHpPriv*)wd->hpPrivate)->usbRxTransferLen = 0;
#endif

    ((struct zsHpPriv*)wd->hpPrivate)->enableBBHeavyClip = 1;
    ((struct zsHpPriv*)wd->hpPrivate)->hwBBHeavyClip     = 1; // force enable 8107
    ((struct zsHpPriv*)wd->hpPrivate)->doBBHeavyClip     = 0;
    ((struct zsHpPriv*)wd->hpPrivate)->setValueHeavyClip = 0;


    /* Initialize driver core */
    zfInitCmdQueue(dev);

    /* Initialize USB */
    zfUsbInit(dev);

#if ZM_SW_LOOP_BACK != 1

    /* TODO : [Download FW] */
    if (wd->modeMDKEnable)
    {
        /* download the MDK firmware */
        if ((ret = zfFirmwareDownload(dev, (u32_t*)zcDKFwImage,
                (u32_t)zcDKFwImageSize, ZM_FIRMWARE_WLAN_ADDR)) != ZM_SUCCESS)
        {
            /* TODO : exception handling */
            //return 1;
        }
    }
    else
    {
    #ifndef ZM_OTUS_LINUX_PHASE_2
        /* download the normal firmware */
        if ((ret = zfFirmwareDownload(dev, (u32_t*)zcFwImage,
                (u32_t)zcFwImageSize, ZM_FIRMWARE_WLAN_ADDR)) != ZM_SUCCESS)
        {
            /* TODO : exception handling */
            //return 1;
        }
    #else

        // 1-PH fw: ReadMac() store some global variable
        if ((ret = zfFirmwareDownloadNotJump(dev, (u32_t*)zcFwBufImage,
                (u32_t)zcFwBufImageSize, 0x102800)) != ZM_SUCCESS)
        {
            DbgPrint("Dl zcFwBufImage failed!");
        }

        zfwSleep(dev, 1000);

        if ((ret = zfFirmwareDownload(dev, (u32_t*)zcFwImage,
                (u32_t)zcFwImageSize, ZM_FIRMWARE_WLAN_ADDR)) != ZM_SUCCESS)
        {
            DbgPrint("Dl zcFwBufImage failed!");
        }
    #endif
    }
#endif

#ifdef ZM_DRV_INIT_USB_MODE
    /* Init USB Mode */
    zfInitUsbMode(dev);

    /* Do the USB Reset */
    zfHpUsbReset(dev);
#endif

/* Register setting */
/* ZM_DRIVER_MODEL_TYPE_MDK
 *  1=>for MDK, disable init RF, PHY, and MAC,
 *  0=>normal init
 */
//#if ((ZM_SW_LOOP_BACK != 1) && (ZM_DRIVER_MODEL_TYPE_MDK !=1))
#if ZM_SW_LOOP_BACK != 1
    if(!wd->modeMDKEnable)
    {
        /* Init MAC */
        zfInitMac(dev);

    #if ZM_FW_LOOP_BACK != 1
        /* Init PHY */
        zfInitPhy(dev, frequency, 0);

        /* Init RF */
        zfInitRf(dev, frequency);

        #if ZM_FPGA_PHY == 0
        /* BringUp issue */
        //zfDelayWriteInternalReg(dev, 0x9800+0x1bc000, 0x10000007);
        //zfFlushDelayWrite(dev);
        #endif

    #endif /* end of ZM_FW_LOOP_BACK != 1 */
    }
#endif /* end of ((ZM_SW_LOOP_BACK != 1) && (ZM_DRIVER_MODEL_TYPE_MDK !=1)) */

    zfHpEchoCommand(dev, 0xAABBCCDD);

    return 0;
}