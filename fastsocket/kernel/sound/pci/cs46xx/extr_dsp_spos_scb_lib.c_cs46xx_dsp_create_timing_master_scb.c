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
typedef  int /*<<< orphan*/  u32 ;
struct snd_cs46xx {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  member_4; int /*<<< orphan*/  member_3; int /*<<< orphan*/  member_2; int /*<<< orphan*/  member_1; int /*<<< orphan*/  member_0; } ;
struct TYPE_3__ {int /*<<< orphan*/  member_3; int /*<<< orphan*/  member_2; int /*<<< orphan*/  member_1; int /*<<< orphan*/  member_0; } ;
struct dsp_timing_master_scb {int member_10; int member_11; int member_12; int member_13; int member_14; int /*<<< orphan*/  member_9; int /*<<< orphan*/  member_8; int /*<<< orphan*/  member_7; int /*<<< orphan*/  member_6; int /*<<< orphan*/  member_5; int /*<<< orphan*/  member_4; int /*<<< orphan*/  member_3; int /*<<< orphan*/  member_2; TYPE_2__ member_1; TYPE_1__ member_0; } ;
struct dsp_scb_descriptor {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  NULL_SCB_ADDR ; 
 int /*<<< orphan*/  SCB_NO_PARENT ; 
 int /*<<< orphan*/  TIMINGMASTER_SCB_ADDR ; 
 struct dsp_scb_descriptor* cs46xx_dsp_create_generic_scb (struct snd_cs46xx*,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

struct dsp_scb_descriptor * 
cs46xx_dsp_create_timing_master_scb (struct snd_cs46xx *chip)
{
	struct dsp_scb_descriptor * scb;
  
	struct dsp_timing_master_scb timing_master_scb = {
		{ 0,
		  0,
		  0,
		  0
		},
		{ 0,
		  0,
		  0,
		  0,
		  0
		},
		0,0,
		0,NULL_SCB_ADDR,
		0,0,             /* extraSampleAccum:TMreserved */
		0,0,             /* codecFIFOptr:codecFIFOsyncd */
		0x0001,0x8000,   /* fracSampAccumQm1:TMfrmsLeftInGroup */
		0x0001,0x0000,   /* fracSampCorrectionQm1:TMfrmGroupLength */
		0x00060000       /* nSampPerFrmQ15 */
	};    
  
	scb = cs46xx_dsp_create_generic_scb(chip,"TimingMasterSCBInst",(u32 *)&timing_master_scb,
					    TIMINGMASTER_SCB_ADDR,
					    "TIMINGMASTER",NULL,SCB_NO_PARENT);

	return scb;
}