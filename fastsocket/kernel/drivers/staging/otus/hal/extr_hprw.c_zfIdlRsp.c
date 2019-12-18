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
typedef  int u8_t ;
typedef  int u32_t ;
typedef  scalar_t__ u16_t ;
struct zsHpPriv {size_t cmdTail; size_t cmdHead; int isSiteSurvey; scalar_t__ freqRetryCounter; int recordFreqRetryCounter; int coldResetNeedFreq; int setValueHeavyClip; int OpFlags; int eepromImageIndex; int* eepromImage; int ctlBusy; int extBusy; scalar_t__ halReInit; int /*<<< orphan*/  eepromImageRdReq; int /*<<< orphan*/  halCapability; scalar_t__ hwBBHeavyClip; scalar_t__ doBBHeavyClip; scalar_t__ enableBBHeavyClip; int /*<<< orphan*/  latestExtOffset; int /*<<< orphan*/  latestBw40; int /*<<< orphan*/  latestFrequency; scalar_t__ cmdPending; TYPE_1__* cmdQ; } ;
typedef  int s32_t ;
struct TYPE_5__ {int* ledMode; } ;
struct TYPE_6__ {struct zsHpPriv* hpPrivate; scalar_t__ aniEnable; TYPE_2__ ledStruct; } ;
struct TYPE_4__ {scalar_t__ cmdLen; int* cmd; } ;

/* Variables and functions */
 scalar_t__ NO_ENUMRD ; 
 scalar_t__ ZM_ANI_READ ; 
 scalar_t__ ZM_CMD_ECHO ; 
 scalar_t__ ZM_CMD_SET_FREQUENCY ; 
 scalar_t__ ZM_CMD_SET_KEY ; 
 scalar_t__ ZM_CWM_READ ; 
 scalar_t__ ZM_EEPROM_READ ; 
 scalar_t__ ZM_EEPROM_WRITE ; 
 scalar_t__ ZM_HAL_MAX_EEPROM_PRQ ; 
 scalar_t__ ZM_HAL_MAX_EEPROM_REQ ; 
 int /*<<< orphan*/  ZM_HP_CAP_11N_ONE_TX_STREAM ; 
 int /*<<< orphan*/  ZM_HP_CAP_2G ; 
 int /*<<< orphan*/  ZM_HP_CAP_5G ; 
 int /*<<< orphan*/  ZM_LV_0 ; 
 scalar_t__ ZM_MAC_READ ; 
 int ZM_MAC_REG_MAC_ADDR_H ; 
 int ZM_MAC_REG_MAC_ADDR_L ; 
 int ZM_MAX_CMD_SIZE ; 
 scalar_t__ ZM_OID_DKTX_STATUS ; 
 scalar_t__ ZM_OID_FLASH_CHKSUM ; 
 scalar_t__ ZM_OID_FLASH_PROGRAM ; 
 scalar_t__ ZM_OID_FLASH_READ ; 
 scalar_t__ ZM_OID_FW_DL_INIT ; 
 scalar_t__ ZM_OID_READ ; 
 scalar_t__ ZM_OID_TALLY ; 
 scalar_t__ ZM_OID_TALLY_APD ; 
 scalar_t__ ZM_OID_WRITE ; 
 int /*<<< orphan*/  ZM_PERFORMANCE_REG (int /*<<< orphan*/ *,int,int) ; 
 int abs (int) ; 
 TYPE_3__* wd ; 
 int /*<<< orphan*/  zfCollectHWTally (int /*<<< orphan*/ *,int*,int) ; 
 int /*<<< orphan*/  zfCoreCwmBusy (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zfCoreHalInitComplete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zfCoreMacAddressNotify (int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  zfCoreSetFrequencyComplete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zfCoreSetKeyComplete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zfCwmIsExtChanBusy (int,int) ; 
 int /*<<< orphan*/  zfDelayWriteInternalReg (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  zfFlushDelayWrite (int /*<<< orphan*/ *) ; 
 scalar_t__ zfGetCmd (int /*<<< orphan*/ *,int*,scalar_t__*,scalar_t__*,int**) ; 
 int /*<<< orphan*/  zfHpAniArPoll (int /*<<< orphan*/ *,int,int,int) ; 
 int /*<<< orphan*/  zfHpGetRegulationTablefromCountry (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  zfHpGetRegulationTablefromRegionCode (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  zfHpLoadEEPROMFromFW (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zfHpSetFrequencyEx (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  zfIdlCmd (int /*<<< orphan*/ *,int*,scalar_t__) ; 
 int /*<<< orphan*/  zfRateCtrlAggrSta (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zfwDbgDownloadFwInitDone (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zfwDbgGetFlashChkSumDone (int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  zfwDbgQueryHwTxBusyDone (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  zfwDbgReadFlashDone (int /*<<< orphan*/ *,int,int*,int) ; 
 int /*<<< orphan*/  zfwDbgReadRegDone (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  zfwDbgReadTallyDone (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zfwDbgWriteEepromDone (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  zfwDbgWriteRegDone (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  zm_assert (int) ; 
 int /*<<< orphan*/  zm_debug_msg0 (char*) ; 
 int /*<<< orphan*/  zm_debug_msg1 (char*,int) ; 
 int /*<<< orphan*/  zm_debug_msg2 (char*,int) ; 
 int /*<<< orphan*/  zm_msg0_mm (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  zm_msg2_mm (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  zmw_declare_for_critical_section () ; 
 int /*<<< orphan*/  zmw_enter_critical_section (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zmw_get_wlan_dev (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zmw_leave_critical_section (int /*<<< orphan*/ *) ; 

void zfIdlRsp(zdev_t* dev, u32_t* rsp, u16_t rspLen)
{
    u32_t cmd[ZM_MAX_CMD_SIZE/4];
    u16_t cmdLen;
    u16_t src;
    u8_t* buf;
    u32_t ncmd[ZM_MAX_CMD_SIZE/4];
    u16_t ncmdLen = 0;
    u16_t ret;
    u16_t cmdFlag = 0;
    u16_t i;
    s32_t nf;
    s32_t noisefloor[4];
    struct zsHpPriv* hpPriv;

    zmw_get_wlan_dev(dev);
    hpPriv=wd->hpPrivate;


    zmw_declare_for_critical_section();

    zmw_enter_critical_section(dev);

    ret = zfGetCmd(dev, cmd, &cmdLen, &src, &buf);
    #if 0
    zm_assert(ret == 0);
    #else
    if (ret != 0)
    {
        zm_debug_msg0("Error IdlRsp because none cmd!!\n");
        #ifndef ZM_XP_USB_MULTCMD
        zmw_leave_critical_section(dev);
        return;
        #endif
    }
    #endif
#ifdef ZM_XP_USB_MULTCMD
    zmw_leave_critical_section(dev);
#else
    if (hpPriv->cmdTail != hpPriv->cmdHead)
    {
        cmdFlag = 1;
        /* Get queueing command */
        ncmdLen= hpPriv->cmdQ[hpPriv->cmdHead].cmdLen;
        for (i=0; i<(ncmdLen>>2); i++)
        {
            ncmd[i] = hpPriv->cmdQ[hpPriv->cmdHead].cmd[i];
        }
    }
    else
    {
        hpPriv->cmdPending = 0;
    }

    zmw_leave_critical_section(dev);

    if (cmdFlag == 1)
    {
        zfIdlCmd(dev, ncmd, ncmdLen);
    }
#endif
    if (src == ZM_OID_READ)
    {
        ZM_PERFORMANCE_REG(dev, 0x11772c, rsp[1]);
        zfwDbgReadRegDone(dev, cmd[1], rsp[1]);
    }
    else if (src == ZM_OID_FLASH_CHKSUM)
    {
        zfwDbgGetFlashChkSumDone(dev, rsp+1);
    }
    else if (src == ZM_OID_FLASH_READ)
    {
        u32_t  datalen;
        u16_t i;

        datalen = (rsp[0] & 255);

        zfwDbgReadFlashDone(dev, cmd[1], rsp+1, datalen);
    }
    else if (src == ZM_OID_FLASH_PROGRAM)
    {
        /* Non do */
    }
    else if (src == ZM_OID_WRITE)
    {
        zfwDbgWriteRegDone(dev, cmd[1], cmd[2]);
    }
    else if (src == ZM_OID_TALLY)
    {
		zfCollectHWTally(dev, rsp, 0);
    }
    else if (src == ZM_OID_TALLY_APD)
    {
		zfCollectHWTally(dev, rsp, 1);
        zfwDbgReadTallyDone(dev);
#ifdef ZM_ENABLE_BA_RATECTRL
        zfRateCtrlAggrSta(dev);
#endif
    }
    else if (src == ZM_OID_DKTX_STATUS)
    {
        zm_debug_msg0("src = zm_OID_DKTX_STATUS");
        zfwDbgQueryHwTxBusyDone(dev, rsp[1]);
    }
    else if (src == ZM_CMD_SET_FREQUENCY)
    {

//#ifdef ZM_OTUS_ENABLE_RETRY_FREQ_CHANGE
#if 0
    zm_debug_msg1("Retry Set Frequency = ", rsp[1]);

    #if 1
    // Read the Noise Floor value !
    nf = ((rsp[2]>>19) & 0x1ff);
    if ((nf & 0x100) != 0x0)
    {
        noisefloor[0] = 0 - ((nf ^ 0x1ff) + 1);
    }
    else
    {
        noisefloor[0] = nf;
    }

    zm_debug_msg1("Noise Floor[1] = ", noisefloor[0]);

    nf = ((rsp[3]>>19) & 0x1ff);
    if ((nf & 0x100) != 0x0)
    {
        noisefloor[1] = 0 - ((nf ^ 0x1ff) + 1);
    }
    else
    {
        noisefloor[1] = nf;
    }

    zm_debug_msg1("Noise Floor[2] = ", noisefloor[1]);
    zm_debug_msg1("Is Site Survey = ", hpPriv->isSiteSurvey);
    #endif

        if ( (rsp[1] && hpPriv->freqRetryCounter == 0) ||
             (((noisefloor[0]>-60)||(noisefloor[1]>-60)) && hpPriv->freqRetryCounter==0) ||
             ((abs(noisefloor[0]-noisefloor[1])>=9) && hpPriv->freqRetryCounter==0) )
        {
            zm_debug_msg0("Retry to issue the frequency change command");

            if ( hpPriv->recordFreqRetryCounter == 1 )
            {
                zm_debug_msg0("Cold Reset");

                zfHpSetFrequencyEx(dev, hpPriv->latestFrequency,
                                        hpPriv->latestBw40,
                                        hpPriv->latestExtOffset,
                                        2);

                if ( hpPriv->isSiteSurvey != 2 )
                {
                    hpPriv->freqRetryCounter++;
                }
                hpPriv->recordFreqRetryCounter = 0;
            }
            else
            {
                zfHpSetFrequencyEx(dev, hpPriv->latestFrequency,
                                        hpPriv->latestBw40,
                                        hpPriv->latestExtOffset,
                                        0);
            }
            hpPriv->recordFreqRetryCounter++;
        }
        else
#endif

/* ret: Bit0: AGC calibration   0=>finish  1=>unfinish               */
/*      Bit1: Noise calibration 0=>finish  1=>unfinish               */
/*      Bit2: Noise calibration finish, but NF value unexcepted => 1 */
        if ( (rsp[1] & 0x1) || (rsp[1] & 0x4) )
        {
            zm_debug_msg1("Set Frequency fail : ret = ", rsp[1]);

            /* 1. AGC Calibration fail                                  */
            /* 2. Noise Calibration finish but error NoiseFloor value   */
            /*      and not in sitesurvey, try more twice               */
            if ( hpPriv->isSiteSurvey == 2 )
            {
                if ( hpPriv->recordFreqRetryCounter < 2 )
                {
                    /* cold reset */
                    zfHpSetFrequencyEx(dev, hpPriv->latestFrequency,
                                            hpPriv->latestBw40,
                                            hpPriv->latestExtOffset,
                                            2);
                    hpPriv->recordFreqRetryCounter++;
                    zm_debug_msg1("Retry to issue the frequency change command(cold reset) counter = ", hpPriv->recordFreqRetryCounter);
                }
                else
                {
                    /* Fail : we would not accept this result! */
                    zm_debug_msg0("\n\n\n\n  Fail twice cold reset \n\n\n\n");
                    hpPriv->coldResetNeedFreq = 0;
                    hpPriv->recordFreqRetryCounter = 0;
                    zfCoreSetFrequencyComplete(dev);
                }
            }
            else
            {
                /* in sitesurvey, coldreset in next channel */
                hpPriv->coldResetNeedFreq = 1;
                hpPriv->recordFreqRetryCounter = 0;
                zfCoreSetFrequencyComplete(dev);
            }
        }
        else if (rsp[1] & 0x2)
        {
            zm_debug_msg1("Set Frequency fail 2 : ret = ", rsp[1]);

            /* Noise Calibration un-finish                          */
            /*      and not in sitesurvey, try more once            */
            if ( hpPriv->isSiteSurvey == 2 )
            {
                if ( hpPriv->recordFreqRetryCounter < 1 )
                {
                    /* cold reset */
                    zfHpSetFrequencyEx(dev, hpPriv->latestFrequency,
                                            hpPriv->latestBw40,
                                            hpPriv->latestExtOffset,
                                            2);
                    hpPriv->recordFreqRetryCounter++;
                    zm_debug_msg1("2 Retry to issue the frequency change command(cold reset) counter = ", hpPriv->recordFreqRetryCounter);
                }
                else
                {
                    /* Fail : we would not accept this result! */
                    zm_debug_msg0("\n\n\n\n  2 Fail twice cold reset \n\n\n\n");
                    hpPriv->coldResetNeedFreq = 0;
                    hpPriv->recordFreqRetryCounter = 0;
                    zfCoreSetFrequencyComplete(dev);
                }
            }
            else
            {
                /* in sitesurvey, skip this frequency */
                hpPriv->coldResetNeedFreq = 0;
                hpPriv->recordFreqRetryCounter = 0;
                zfCoreSetFrequencyComplete(dev);
            }
        }
        //else if (rsp[1] & 0x4)
        //{
        //    zm_debug_msg1("Set Frequency fail 3 : ret = ", rsp[1]);
        //    hpPriv->coldResetNeedFreq = 0;
        //    hpPriv->recordFreqRetryCounter = 0;
        //    zfCoreSetFrequencyComplete(dev);
        //}
        else
        {
            //hpPriv->freqRetryCounter = 0;
            zm_debug_msg2(" return complete, ret = ", rsp[1]);

            /* set bb_heavy_clip_enable */
            if (hpPriv->enableBBHeavyClip && hpPriv->hwBBHeavyClip &&
                hpPriv->doBBHeavyClip)
            {
                u32_t setValue = 0x200;

                setValue |= hpPriv->setValueHeavyClip;

                //zm_dbg(("Do heavy clip setValue = %d\n", setValue));

                zfDelayWriteInternalReg(dev, 0x99e0+0x1bc000, setValue);
                zfFlushDelayWrite(dev);
            }

            hpPriv->coldResetNeedFreq = 0;
            hpPriv->recordFreqRetryCounter = 0;
    	    zfCoreSetFrequencyComplete(dev);
    	}

        #if 1
        // Read the Noise Floor value !
        nf = ((rsp[2]>>19) & 0x1ff);
        if ((nf & 0x100) != 0x0)
        {
            noisefloor[0] = 0 - ((nf ^ 0x1ff) + 1);
        }
        else
        {
            noisefloor[0] = nf;
        }

        //zm_debug_msg1("Noise Floor[1] = ", noisefloor[0]);

        nf = ((rsp[3]>>19) & 0x1ff);
        if ((nf & 0x100) != 0x0)
        {
            noisefloor[1] = 0 - ((nf ^ 0x1ff) + 1);
        }
        else
        {
            noisefloor[1] = nf;
        }

        //zm_debug_msg1("Noise Floor[2] = ", noisefloor[1]);

        nf = ((rsp[5]>>23) & 0x1ff);
        if ((nf & 0x100) != 0x0)
        {
            noisefloor[2] = 0 - ((nf ^ 0x1ff) + 1);
        }
        else
        {
            noisefloor[2] = nf;
        }

        //zm_debug_msg1("Noise Floor ext[1] = ", noisefloor[2]);

        nf = ((rsp[6]>>23) & 0x1ff);
        if ((nf & 0x100) != 0x0)
        {
            noisefloor[3] = 0 - ((nf ^ 0x1ff) + 1);
        }
        else
        {
            noisefloor[3] = nf;
        }

        //zm_debug_msg1("Noise Floor ext[2] = ", noisefloor[3]);

        //zm_debug_msg1("Is Site Survey = ", hpPriv->isSiteSurvey);
        #endif
    }
    else if (src == ZM_CMD_SET_KEY)
    {
        zfCoreSetKeyComplete(dev);
    }
    else if (src == ZM_CWM_READ)
    {
        zm_msg2_mm(ZM_LV_0, "CWM rsp[1]=", rsp[1]);
        zm_msg2_mm(ZM_LV_0, "CWM rsp[2]=", rsp[2]);
        zfCoreCwmBusy(dev, zfCwmIsExtChanBusy(rsp[1], rsp[2]));
    }
    else if (src == ZM_MAC_READ)
    {
        /* rsp[1] = ZM_SEEPROM_MAC_ADDRESS_OFFSET;   */
        /* rsp[2] = ZM_SEEPROM_MAC_ADDRESS_OFFSET+4; */
        /* rsp[3] = ZM_SEEPROM_REGDOMAIN_OFFSET;     */
        /* rsp[4] = ZM_SEEPROM_VERISON_OFFSET;       */
        /* rsp[5] = ZM_SEEPROM_HARDWARE_TYPE_OFFSET; */
        /* rsp[6] = ZM_SEEPROM_HW_HEAVY_CLIP;        */

        u8_t addr[6], CCS, WWR;
        u16_t CountryDomainCode;

        /* BB heavy clip */
        //hpPriv->eepromHeavyClipFlag = (u8_t)((rsp[6]>>24) & 0xff); // force enable 8107
        //zm_msg2_mm(ZM_LV_0, "eepromHeavyClipFlag", hpPriv->eepromHeavyClipFlag);
        #if 0
        if (hpPriv->hwBBHeavyClip)
        {
            zm_msg0_mm(ZM_LV_0, "enable BB Heavy Clip");
        }
        else
        {
            zm_msg0_mm(ZM_LV_0, "Not enable BB Heavy Clip");
        }
        #endif
        zm_msg2_mm(ZM_LV_0, "MAC rsp[1]=", rsp[1]);
        zm_msg2_mm(ZM_LV_0, "MAC rsp[2]=", rsp[2]);

        addr[0] = (u8_t)(rsp[1] & 0xff);
        addr[1] = (u8_t)((rsp[1]>>8) & 0xff);
        addr[2] = (u8_t)((rsp[1]>>16) & 0xff);
        addr[3] = (u8_t)((rsp[1]>>24) & 0xff);
        addr[4] = (u8_t)(rsp[2] & 0xff);
        addr[5] = (u8_t)((rsp[2]>>8) & 0xff);
/*#ifdef ZM_FB50
        addr[0] = (u8_t)(0 & 0xff);
        addr[1] = (u8_t)(3 & 0xff);
        addr[2] = (u8_t)(127 & 0xff);
        addr[3] = (u8_t)(0 & 0xff);
        addr[4] = (u8_t)(9 & 0xff);
        addr[5] = (u8_t)(11 & 0xff);
#endif*/

        zfDelayWriteInternalReg(dev, ZM_MAC_REG_MAC_ADDR_L,
                ((((u32_t)addr[3])<<24) | (((u32_t)addr[2])<<16) | (((u32_t)addr[1])<<8) | addr[0]));
        zfDelayWriteInternalReg(dev, ZM_MAC_REG_MAC_ADDR_H,
                ((((u32_t)addr[5])<<8) | addr[4]));
        zfFlushDelayWrite(dev);

        wd->ledStruct.ledMode[0] = (u16_t)(rsp[5]&0xffff);
        wd->ledStruct.ledMode[1] = (u16_t)(rsp[5]>>16);
        zm_msg2_mm(ZM_LV_0, "ledMode[0]=", wd->ledStruct.ledMode[0]);
        zm_msg2_mm(ZM_LV_0, "ledMode[1]=", wd->ledStruct.ledMode[1]);

        /* Regulatory Related Setting */
        zm_msg2_mm(ZM_LV_0, "RegDomain rsp=", rsp[3]);
        zm_msg2_mm(ZM_LV_0, "OpFlags+EepMisc=", rsp[4]);
        hpPriv->OpFlags = (u8_t)((rsp[4]>>16) & 0xff);
        if ((rsp[2] >> 24) == 0x1) //Tx mask == 0x1
        {
            zm_msg0_mm(ZM_LV_0, "OTUS 1x2");
            hpPriv->halCapability |= ZM_HP_CAP_11N_ONE_TX_STREAM;
        }
        else
        {
            zm_msg0_mm(ZM_LV_0, "OTUS 2x2");
        }
        if (hpPriv->OpFlags & 0x1)
        {
            hpPriv->halCapability |= ZM_HP_CAP_5G;
        }
        if (hpPriv->OpFlags & 0x2)
        {
            hpPriv->halCapability |= ZM_HP_CAP_2G;
        }


        CCS = (u8_t)((rsp[3] & 0x8000) >> 15);
        WWR = (u8_t)((rsp[3] & 0x4000) >> 14);
        CountryDomainCode = (u16_t)(rsp[3] & 0x3FFF);

        if (rsp[3] != 0xffffffff)
        {
            if (CCS)
            {
                //zm_debug_msg0("CWY - Get Regulation Table from Country Code");
                zfHpGetRegulationTablefromCountry(dev, CountryDomainCode);
            }
            else
            {
                //zm_debug_msg0("CWY - Get Regulation Table from Reg Domain");
                zfHpGetRegulationTablefromRegionCode(dev, CountryDomainCode);
            }
            if (WWR)
            {
                //zm_debug_msg0("CWY - Enable 802.11d");
                /* below line shall be unmarked after A band is ready */
                //zfiWlanSetDot11DMode(dev, 1);
            }
        }
        else
        {
            zfHpGetRegulationTablefromRegionCode(dev, NO_ENUMRD);
        }

        zfCoreMacAddressNotify(dev, addr);

    }
    else if (src == ZM_EEPROM_READ)
    {
#if 0
        u8_t addr[6], CCS, WWR;
        u16_t CountryDomainCode;
#endif
        for (i=0; i<ZM_HAL_MAX_EEPROM_PRQ; i++)
        {
            if (hpPriv->eepromImageIndex < 1024)
            {
                hpPriv->eepromImage[hpPriv->eepromImageIndex++] = rsp[i+1];
            }
        }

        if (hpPriv->eepromImageIndex == (ZM_HAL_MAX_EEPROM_REQ*ZM_HAL_MAX_EEPROM_PRQ))
        {
            #if 0
            for (i=0; i<1024; i++)
            {
                zm_msg2_mm(ZM_LV_0, "index=", i);
                zm_msg2_mm(ZM_LV_0, "eepromImage=", hpPriv->eepromImage[i]);
            }
            #endif
            zm_msg2_mm(ZM_LV_0, "MAC [1]=", hpPriv->eepromImage[0x20c/4]);
            zm_msg2_mm(ZM_LV_0, "MAC [2]=", hpPriv->eepromImage[0x210/4]);
#if 0
            addr[0] = (u8_t)(hpPriv->eepromImage[0x20c/4] & 0xff);
            addr[1] = (u8_t)((hpPriv->eepromImage[0x20c/4]>>8) & 0xff);
            addr[2] = (u8_t)((hpPriv->eepromImage[0x20c/4]>>16) & 0xff);
            addr[3] = (u8_t)((hpPriv->eepromImage[0x20c/4]>>24) & 0xff);
            addr[4] = (u8_t)(hpPriv->eepromImage[0x210/4] & 0xff);
            addr[5] = (u8_t)((hpPriv->eepromImage[0x210/4]>>8) & 0xff);

            zfCoreMacAddressNotify(dev, addr);

            zfDelayWriteInternalReg(dev, ZM_MAC_REG_MAC_ADDR_L,
                    ((((u32_t)addr[3])<<24) | (((u32_t)addr[2])<<16) | (((u32_t)addr[1])<<8) | addr[0]));
            zfDelayWriteInternalReg(dev, ZM_MAC_REG_MAC_ADDR_H,
                    ((((u32_t)addr[5])<<8) | addr[4]));
            zfFlushDelayWrite(dev);

            /* Regulatory Related Setting */
            zm_msg2_mm(ZM_LV_0, "RegDomain =", hpPriv->eepromImage[0x208/4]);
            CCS = (u8_t)((hpPriv->eepromImage[0x208/4] & 0x8000) >> 15);
            WWR = (u8_t)((hpPriv->eepromImage[0x208/4] & 0x4000) >> 14);
            /* below line shall be unmarked after A band is ready */
            //CountryDomainCode = (u16_t)(hpPriv->eepromImage[0x208/4] & 0x3FFF);
            CountryDomainCode = 8;
            if (CCS)
            {
                //zm_debug_msg0("CWY - Get Regulation Table from Country Code");
                zfHpGetRegulationTablefromCountry(dev, CountryDomainCode);
            }
            else
            {
                //zm_debug_msg0("CWY - Get Regulation Table from Reg Domain");
                zfHpGetRegulationTablefromRegionCode(dev, CountryDomainCode);
            }
            if (WWR)
            {
                //zm_debug_msg0("CWY - Enable 802.11d");
                /* below line shall be unmarked after A band is ready */
                //zfiWlanSetDot11DMode(dev, 1);
            }
#endif
            zfCoreHalInitComplete(dev);
        }
        else
        {
            hpPriv->eepromImageRdReq++;
            zfHpLoadEEPROMFromFW(dev);
        }
    }
    else if (src == ZM_EEPROM_WRITE)
    {
        zfwDbgWriteEepromDone(dev, cmd[1], cmd[2]);
    }
    else if (src == ZM_ANI_READ)
    {
        u32_t cycleTime, ctlClear;

        zm_msg2_mm(ZM_LV_0, "ANI rsp[1]=", rsp[1]);
        zm_msg2_mm(ZM_LV_0, "ANI rsp[2]=", rsp[2]);
        zm_msg2_mm(ZM_LV_0, "ANI rsp[3]=", rsp[3]);
        zm_msg2_mm(ZM_LV_0, "ANI rsp[4]=", rsp[4]);

        hpPriv->ctlBusy += rsp[1];
        hpPriv->extBusy += rsp[2];

        cycleTime = 100000; //100 miniseconds

        if (cycleTime > rsp[1])
        {
            ctlClear = (cycleTime - rsp[1]) / 100;
        }
        else
        {
            ctlClear = 0;
        }
        if (wd->aniEnable)
            zfHpAniArPoll(dev, ctlClear, rsp[3], rsp[4]);
    }
    else if (src == ZM_CMD_ECHO)
    {
        if ( ((struct zsHpPriv*)wd->hpPrivate)->halReInit )
        {
            zfCoreHalInitComplete(dev);
            ((struct zsHpPriv*)wd->hpPrivate)->halReInit = 0;
        }
        else
        {
            zfHpLoadEEPROMFromFW(dev);
        }
    }
    else if (src == ZM_OID_FW_DL_INIT)
    {
        zfwDbgDownloadFwInitDone(dev);
    }
    return;
}