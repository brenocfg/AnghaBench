#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zdev_t ;
typedef  int /*<<< orphan*/  u64_t ;
typedef  size_t u32_t ;
typedef  scalar_t__ u16_t ;
struct zsHpPriv {int OpFlags; scalar_t__ disableDfsCh; } ;
struct cmode {int mode; int /*<<< orphan*/  flags; } ;
typedef  int s16_t ;
struct TYPE_10__ {int privFlags; int /*<<< orphan*/  maxRegTxPower; int /*<<< orphan*/  channelFlags; scalar_t__ channel; scalar_t__ maxTxPower; scalar_t__ minTxPower; } ;
typedef  TYPE_2__ ZM_HAL_CHANNEL ;
struct TYPE_9__ {scalar_t__ regionCode; int allowChannelCnt; TYPE_2__* allowChannel; } ;
struct TYPE_13__ {TYPE_1__ regulationTable; struct zsHpPriv* hpPrivate; } ;
struct TYPE_12__ {scalar_t__ lowChannel; scalar_t__ highChannel; scalar_t__ channelSep; int useDfs; int channelBW; int usePassScan; int /*<<< orphan*/  powerDfs; } ;
struct TYPE_11__ {int dfsMask; int pscan; int flags; int /*<<< orphan*/ * chan11g; int /*<<< orphan*/ * chan11a; } ;
typedef  TYPE_3__ REG_DOMAIN ;
typedef  TYPE_4__ REG_DMN_FREQ_BAND ;

/* Variables and functions */
 int BMLEN ; 
 int DFS_FCC3 ; 
 int /*<<< orphan*/  DbgPrint (char*,...) ; 
 int /*<<< orphan*/  GetWmRD (scalar_t__,int /*<<< orphan*/ ,TYPE_3__*) ; 
#define  HAL_MODE_11A 133 
#define  HAL_MODE_11A_TURBO 132 
#define  HAL_MODE_11B 131 
#define  HAL_MODE_11G 130 
#define  HAL_MODE_11G_TURBO 129 
#define  HAL_MODE_TURBO 128 
 scalar_t__ IS_BIT_SET (int,int /*<<< orphan*/ *) ; 
 int LIMIT_FRAME_4MS ; 
 size_t N (struct cmode const*) ; 
 int /*<<< orphan*/  ZM_REG_FLAG_CHANNEL_2GHZ ; 
 int ZM_REG_FLAG_CHANNEL_DFS ; 
 int ZM_REG_FLAG_CHANNEL_DFS_CLEAR ; 
 int /*<<< orphan*/  ZM_REG_FLAG_CHANNEL_PASSIVE ; 
 scalar_t__ isChanBitMaskZero (int /*<<< orphan*/ *) ; 
 struct cmode const* modes ; 
 TYPE_4__* regDmn2Ghz11gFreq ; 
 TYPE_4__* regDmn5GhzFreq ; 
 TYPE_5__* wd ; 
 int /*<<< orphan*/  zm_assert (int) ; 
 int /*<<< orphan*/  zm_debug_msg1 (char*,scalar_t__) ; 
 int /*<<< orphan*/  zmw_declare_for_critical_section () ; 
 int /*<<< orphan*/  zmw_enter_critical_section (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zmw_get_wlan_dev (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zmw_leave_critical_section (int /*<<< orphan*/ *) ; 

void zfHpGetRegulationTable(zdev_t* dev, u16_t regionCode, u16_t c_lo, u16_t c_hi)
{
	REG_DOMAIN rd5GHz, rd2GHz;
	const struct cmode *cm;
	s16_t next=0,b;
	struct zsHpPriv* hpPriv;

    zmw_get_wlan_dev(dev);
    hpPriv=wd->hpPrivate;

    zmw_declare_for_critical_section();

	if (!GetWmRD(regionCode, ~ZM_REG_FLAG_CHANNEL_2GHZ, &rd5GHz))
	{
        zm_debug_msg1("couldn't find unitary 5GHz reg domain for Region Code ", regionCode);
		return;
	}
	if (!GetWmRD(regionCode, ZM_REG_FLAG_CHANNEL_2GHZ, &rd2GHz))
	{
        zm_debug_msg1("couldn't find unitary 2GHz reg domain for Region Code ", regionCode);
		return;
	}
    if (wd->regulationTable.regionCode == regionCode)
    {
        zm_debug_msg1("current region code is the same with Region Code ", regionCode);
        return;
    }
    else
    {
        wd->regulationTable.regionCode = regionCode;
    }

    next = 0;

    zmw_enter_critical_section(dev);

	for (cm = modes; cm < &modes[N(modes)]; cm++)
	{
		u16_t c;
		u64_t *channelBM=NULL;
		REG_DOMAIN *rd=NULL;
		REG_DMN_FREQ_BAND *fband=NULL,*freqs=NULL;

		switch (cm->mode)
		{
		case HAL_MODE_TURBO:
		    //we don't have turbo mode so we disable it
            //zm_debug_msg0("CWY - HAL_MODE_TURBO");
            channelBM = NULL;
			//rd = &rd5GHz;
			//channelBM = rd->chan11a_turbo;
			//freqs = &regDmn5GhzTurboFreq[0];
			//ctl = rd->conformanceTestLimit | CTL_TURBO;
			break;
		case HAL_MODE_11A:
		    if ((hpPriv->OpFlags & 0x1) != 0)
		    {
    			rd = &rd5GHz;
    			channelBM = rd->chan11a;
    			freqs = &regDmn5GhzFreq[0];
    			c_lo = 4920; //from channel 184
    			c_hi = 5825; //to   channel 165
    			//ctl = rd->conformanceTestLimit;
                //zm_debug_msg2("CWY - HAL_MODE_11A, channelBM = 0x", *channelBM);
            }
            //else
            {
                //channelBM = NULL;
            }
			break;
		case HAL_MODE_11B:
		    //Disable 11B mode because it only has difference with 11G in PowerDFS Data,
		    //and we don't use this now.
			//zm_debug_msg0("CWY - HAL_MODE_11B");
			channelBM = NULL;
			//rd = &rd2GHz;
			//channelBM = rd->chan11b;
			//freqs = &regDmn2GhzFreq[0];
			//ctl = rd->conformanceTestLimit | CTL_11B;
            //zm_debug_msg2("CWY - HAL_MODE_11B, channelBM = 0x", *channelBM);
			break;
		case HAL_MODE_11G:
		    if ((hpPriv->OpFlags & 0x2) != 0)
		    {
    			rd = &rd2GHz;
    			channelBM = rd->chan11g;
    			freqs = &regDmn2Ghz11gFreq[0];
    			c_lo = 2412; //from channel  1
    			//c_hi = 2462; //to   channel 11
                c_hi = 2472; //to   channel 13
    			//ctl = rd->conformanceTestLimit | CTL_11G;
                //zm_debug_msg2("CWY - HAL_MODE_11G, channelBM = 0x", *channelBM);
            }
            //else
            {
                //channelBM = NULL;
            }
			break;
		case HAL_MODE_11G_TURBO:
		    //we don't have turbo mode so we disable it
            //zm_debug_msg0("CWY - HAL_MODE_11G_TURBO");
            channelBM = NULL;
			//rd = &rd2GHz;
			//channelBM = rd->chan11g_turbo;
			//freqs = &regDmn2Ghz11gTurboFreq[0];
			//ctl = rd->conformanceTestLimit | CTL_108G;
			break;
		case HAL_MODE_11A_TURBO:
		    //we don't have turbo mode so we disable it
            //zm_debug_msg0("CWY - HAL_MODE_11A_TURBO");
            channelBM = NULL;
			//rd = &rd5GHz;
			//channelBM = rd->chan11a_dyn_turbo;
			//freqs = &regDmn5GhzTurboFreq[0];
			//ctl = rd->conformanceTestLimit | CTL_108G;
			break;
		default:
            zm_debug_msg1("Unkonwn HAL mode ", cm->mode);
			continue;
		}
		if (channelBM == NULL)
		{
		    //zm_debug_msg0("CWY - channelBM is NULL");
		    continue;
        }
        if (isChanBitMaskZero(channelBM))
        {
	        //zm_debug_msg0("CWY - BitMask is Zero");
	        continue;
        }

        // RAY:Is it ok??
        if (freqs == NULL )
        {
            continue;
        }

		for (b=0;b<64*BMLEN; b++)
		{
			if (IS_BIT_SET(b,channelBM))
			{
				fband = &freqs[b];

				//zm_debug_msg1("CWY - lowChannel = ", fband->lowChannel);
				//zm_debug_msg1("CWY - highChannel = ", fband->highChannel);
				//zm_debug_msg1("CWY - channelSep = ", fband->channelSep);
				for (c=fband->lowChannel; c <= fband->highChannel;
				     c += fband->channelSep)
				{
					ZM_HAL_CHANNEL icv;

                    //Disable all DFS channel
                    if ((hpPriv->disableDfsCh==0) || (!(fband->useDfs & rd->dfsMask)))
                    {
                        if( fband->channelBW < 20 )
                        {
                        	/**************************************************************/
                            /*                                                            */
                            /*   Temporary discard channel that BW < 20MHz (5 or 10MHz)   */
                            /*   Our architecture does not implemnt it !!!                */
                            /*                                                            */
                            /**************************************************************/
                            continue;
                        }
					if ((c >= c_lo) && (c <= c_hi))
					{
					    icv.channel = c;
					    icv.channelFlags = cm->flags;
					    icv.maxRegTxPower = fband->powerDfs;
					    if (fband->usePassScan & rd->pscan)
					    	icv.channelFlags |= ZM_REG_FLAG_CHANNEL_PASSIVE;
					    else
					    	icv.channelFlags &= ~ZM_REG_FLAG_CHANNEL_PASSIVE;
					    if (fband->useDfs & rd->dfsMask)
					    	icv.privFlags = ZM_REG_FLAG_CHANNEL_DFS;
					    else
					    	icv.privFlags = 0;

					    /* For now disable radar for FCC3 */
					    if (fband->useDfs & rd->dfsMask & DFS_FCC3)
					    {
					    	icv.privFlags &= ~ZM_REG_FLAG_CHANNEL_DFS;
					    	icv.privFlags |= ZM_REG_FLAG_CHANNEL_DFS_CLEAR;
					    }

					    if(rd->flags & LIMIT_FRAME_4MS)
					    	icv.privFlags |= ZM_REG_FLAG_CHANNEL_DFS_CLEAR;

					    icv.minTxPower = 0;
					    icv.maxTxPower = 0;

        			    zm_assert(next < 60);

					    wd->regulationTable.allowChannel[next++] = icv;
				    }
				}
			}
		}
	}
	}
	wd->regulationTable.allowChannelCnt = next;

    #if 0
    {
        /* debug print */
        u32_t i;
        DbgPrint("\n-------------------------------------------\n");
        DbgPrint("zfHpGetRegulationTable print all channel info regincode = 0x%x\n", wd->regulationTable.regionCode);
        DbgPrint("index  channel  channelFlags   maxRegTxPower  privFlags  useDFS\n");

        for (i=0; i<wd->regulationTable.allowChannelCnt; i++)
        {
            DbgPrint("%02d       %d         %04x           %02d        %x     %x\n",
                      i,
                      wd->regulationTable.allowChannel[i].channel,
                      wd->regulationTable.allowChannel[i].channelFlags,
                      wd->regulationTable.allowChannel[i].maxRegTxPower,
                      wd->regulationTable.allowChannel[i].privFlags,
                      wd->regulationTable.allowChannel[i].privFlags & ZM_REG_FLAG_CHANNEL_DFS);
        }
    }
    #endif

    zmw_leave_critical_section(dev);
}