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
typedef  int u8_t ;
typedef  int u32_t ;
typedef  int u16_t ;
struct TYPE_3__ {int* authAlgo; int authSharing; scalar_t__* challengeText; } ;
struct TYPE_4__ {TYPE_1__ ap; } ;

/* Variables and functions */
 int /*<<< orphan*/  ZM_LV_0 ; 
 int /*<<< orphan*/  ZM_STATE_AUTH ; 
 int /*<<< orphan*/  ZM_STATE_PREAUTH ; 
 int /*<<< orphan*/  ZM_WLAN_FRAME_TYPE_AUTH ; 
 TYPE_2__* wd ; 
 int zfApAddSta (int /*<<< orphan*/ *,int*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zfSendMmFrame (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int*,int,int,int) ; 
 int /*<<< orphan*/  zm_msg2_mm (int /*<<< orphan*/ ,char*,int) ; 
 scalar_t__ zmw_buf_readb (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int zmw_buf_readh (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  zmw_declare_for_critical_section () ; 
 int /*<<< orphan*/  zmw_enter_critical_section (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zmw_get_wlan_dev (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zmw_leave_critical_section (int /*<<< orphan*/ *) ; 
 int zmw_rx_buf_readb (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int zmw_rx_buf_readh (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

void zfApProcessAuth(zdev_t* dev, zbuf_t* buf, u16_t* src, u16_t apId)
{
    u16_t algo, seq, status;
    u8_t authSharing;
    u16_t ret;
    u16_t i;
    u8_t challengePassed = 0;
    u8_t frameCtrl;
    u32_t retAlgoSeq;
    u32_t retStatus;
    zmw_get_wlan_dev(dev);
    zmw_declare_for_critical_section();


    frameCtrl = zmw_rx_buf_readb(dev, buf, 1);
    /* AP : Auth share 3 */
    /* shift for WEP IV */
    if ((frameCtrl & 0x40) != 0)
    {
        algo = zmw_rx_buf_readh(dev, buf, 28);
        seq = zmw_rx_buf_readh(dev, buf, 30);
        status = zmw_rx_buf_readh(dev, buf, 32);
    }
    else
    {
        algo = zmw_rx_buf_readh(dev, buf, 24);
        seq = zmw_rx_buf_readh(dev, buf, 26);
        status = zmw_rx_buf_readh(dev, buf, 28);
    }

    zm_msg2_mm(ZM_LV_0, "Rx Auth, seq=", seq);

    /* Set default to authentication algorithm not support */
    retAlgoSeq = 0x20000 | algo;
    retStatus = 13; /* authentication algorithm not support */

    /* AP : Auth open 1 */
    if (algo == 0)
    {
        if (wd->ap.authAlgo[apId] == 0)
        {
            retAlgoSeq = 0x20000;
            if (seq == 1)
            {
                /* AP : update STA to auth */
                if ((ret = zfApAddSta(dev, src, ZM_STATE_AUTH, apId, 0, 0, 0)) != 0xffff)
                {
                    /* AP : call zfwAuthNotify() for host to judge */
                    //zfwAuthNotify(dev, src);

                    /* AP : response Auth seq=2, success */
                    retStatus = 0;

                }
                else
                {
                    /* AP : response Auth seq=2, unspecific error */
                    retStatus = 1;
                }
            }
            else
            {
                /* AP : response Auth seq=2, sequence number out of expected */
                retStatus = 14;
            }
        }
    }
    /* AP : Auth share 1 */
    else if (algo == 1)
    {
        if (wd->ap.authAlgo[apId] == 1)
        {
            if (seq == 1)
            {
                retAlgoSeq = 0x20001;

                /* critical section */
                zmw_enter_critical_section(dev);
                if (wd->ap.authSharing == 1)
                {
                    authSharing = 1;
                }
                else
                {
                    authSharing = 0;
                    wd->ap.authSharing = 1;
                }
                /* end of critical section */
                zmw_leave_critical_section(dev);

                if (authSharing == 1)
                {
                    /* AP : response Auth seq=2, status = fail */
                    retStatus = 1;
                }
                else
                {
                    /* AP : update STA to preauth */
                    zfApAddSta(dev, src, ZM_STATE_PREAUTH, apId, 0, 0, 0);

                    /* AP : call zfwAuthNotify() for host to judge */
                    //zfwAuthNotify(dev, src);

                    /* AP : response Auth seq=2 */
                    retStatus = 0;
                }
            }
            else if (seq == 3)
            {
                retAlgoSeq = 0x40001;

                if (wd->ap.authSharing == 1)
                {
                    /* check challenge text */
                    if (zmw_buf_readh(dev, buf, 30+4) == 0x8010)
                    {
                        for (i=0; i<128; i++)
                        {
                            if (wd->ap.challengeText[i]
                                        != zmw_buf_readb(dev, buf, 32+i+4))
                            {
                                break;
                            }
                        }
                        if (i == 128)
                        {
                            challengePassed = 1;
                        }
                    }

                    if (challengePassed == 1)
                    {
                        /* AP : update STA to auth */
                        zfApAddSta(dev, src, ZM_STATE_AUTH, apId, 0, 0, 0);

                        /* AP : response Auth seq=2 */
                        retStatus = 0;
                    }
                    else
                    {
                        /* AP : response Auth seq=2, challenge failure */
                        retStatus = 15;

                        /* TODO : delete STA */
                    }

                    wd->ap.authSharing = 0;
                }
            }
            else
            {
                retAlgoSeq = 0x40001;
                retStatus = 14;
            }
        }
    }

    zfSendMmFrame(dev, ZM_WLAN_FRAME_TYPE_AUTH, src, retAlgoSeq,
            retStatus, apId);
    return;
}