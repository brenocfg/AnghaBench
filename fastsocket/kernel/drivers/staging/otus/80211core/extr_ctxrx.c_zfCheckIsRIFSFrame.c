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
struct TYPE_3__ {int* rifsLikeFrameSequence; size_t rifsLikeFrameCnt; scalar_t__ rifsState; int currentFrequency; scalar_t__ rifsTimer; int /*<<< orphan*/  rifsCount; int /*<<< orphan*/  HT2040; int /*<<< orphan*/  EnableHT; } ;
struct TYPE_4__ {scalar_t__ tick; TYPE_1__ sta; } ;

/* Variables and functions */
 int ZM_BIT_5 ; 
 scalar_t__ ZM_RIFS_STATE_DETECTED ; 
 scalar_t__ ZM_RIFS_STATE_DETECTING ; 
 scalar_t__ ZM_RIFS_TIMER_TIMEOUT ; 
 TYPE_2__* wd ; 
 int /*<<< orphan*/  zfHpDisableRifs (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zfHpEnableRifs (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int zmw_buf_readh (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  zmw_get_wlan_dev (int /*<<< orphan*/ *) ; 

void zfCheckIsRIFSFrame(zdev_t* dev, zbuf_t* buf, u16_t frameSubtype)
{
    zmw_get_wlan_dev(dev);

    /* #2 Record the sequence number to determine whether the unicast frame is separated by RIFS or not */
    if (frameSubtype & 0x80)
    {   //QoS data frame
        u16_t sequenceNum;
        u16_t qosControlField;

        sequenceNum = ( zmw_buf_readh(dev, buf, 22) >> 4 ); // Discard fragment number !
        qosControlField = zmw_buf_readh(dev, buf, 24); // Don't consider WDS (Wireless Distribution System)
        //DbgPrint("The QoS Control Field                              : %d", qosControlField);
        //DbgPrint("The RIFS Count                                     : %d", wd->sta.rifsCount);

        if( qosControlField & ZM_BIT_5 )
        {// ACK policy is "No ACK"
            /* RIFS-Like frame */
            wd->sta.rifsLikeFrameSequence[wd->sta.rifsLikeFrameCnt]   = sequenceNum;

            if( wd->sta.rifsState == ZM_RIFS_STATE_DETECTING )
            {
                if( wd->sta.rifsLikeFrameSequence[2] != 0 )
                {// RIFS-like Pattern collected
                    if( ( wd->sta.rifsLikeFrameSequence[2] - wd->sta.rifsLikeFrameSequence[1] == 2 ) &&
                        ( wd->sta.rifsLikeFrameSequence[1] - wd->sta.rifsLikeFrameSequence[0] == 2 ) )
                    {
                        /* RIFS pattern matched */

                        /* #3 Enable RIFS function if the RIFS pattern matched  */
                        zfHpEnableRifs(dev, ((wd->sta.currentFrequency<3000)?1:0), wd->sta.EnableHT, wd->sta.HT2040);

                        // Set RIFS timer
                        wd->sta.rifsTimer = wd->tick;

                        wd->sta.rifsCount++;

                        // Set state to be Detected
                        wd->sta.rifsState = ZM_RIFS_STATE_DETECTED;
                    }
                }
            }
            else
            {// state = Detected
                // Reset RIFS timer
                if( (wd->tick - wd->sta.rifsTimer) < ZM_RIFS_TIMER_TIMEOUT )
                    wd->sta.rifsTimer = wd->tick;
            }

            //DbgPrint("SN1 = %d, SN2 = %d, SN3 = %d\n", wd->sta.rifsLikeFrameSequence[0],
            //                                           wd->sta.rifsLikeFrameSequence[1],
            //                                           wd->sta.rifsLikeFrameSequence[2]);

            // Update RIFS-like sequence number
            if( wd->sta.rifsLikeFrameSequence[2] != 0 )
            {
                wd->sta.rifsLikeFrameSequence[0] = wd->sta.rifsLikeFrameSequence[1];
                wd->sta.rifsLikeFrameSequence[1] = wd->sta.rifsLikeFrameSequence[2];
                wd->sta.rifsLikeFrameSequence[2] = 0;
            }

            // Only record three adjacent frame
            if( wd->sta.rifsLikeFrameCnt < 2 )
                wd->sta.rifsLikeFrameCnt++;
        }
    }

    /* #4 Disable RIFS function if the timer TIMEOUT  */
    if( wd->sta.rifsState == ZM_RIFS_STATE_DETECTED )
    {
        if( ( wd->tick - wd->sta.rifsTimer ) > ZM_RIFS_TIMER_TIMEOUT )
        {// TIMEOUT
            // Disable RIFS
            zfHpDisableRifs(dev);

            // Reset RIFS-like sequence number FIFO
            wd->sta.rifsLikeFrameSequence[0] = 0;
            wd->sta.rifsLikeFrameSequence[1] = 0;
            wd->sta.rifsLikeFrameSequence[2] = 0;
            wd->sta.rifsLikeFrameCnt = 0;

            // Set state to be Detecting
            wd->sta.rifsState = ZM_RIFS_STATE_DETECTING;
        }
    }
}