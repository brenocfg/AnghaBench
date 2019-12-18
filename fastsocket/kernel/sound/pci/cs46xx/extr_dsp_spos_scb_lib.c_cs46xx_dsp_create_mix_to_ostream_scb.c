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
typedef  int u32 ;
typedef  scalar_t__ u16 ;
struct snd_cs46xx {int dummy; } ;
struct dsp_scb_descriptor {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  member_4; int /*<<< orphan*/  member_3; int /*<<< orphan*/  member_2; int /*<<< orphan*/  member_1; int /*<<< orphan*/  member_0; } ;
struct TYPE_3__ {int member_3; scalar_t__ member_2; scalar_t__ member_1; int /*<<< orphan*/  member_0; } ;
struct dsp_mix2_ostream_scb {int member_6; int member_7; int member_8; int member_10; int member_11; int member_12; int /*<<< orphan*/  member_13; int /*<<< orphan*/  member_9; scalar_t__ member_5; int /*<<< orphan*/  member_4; int /*<<< orphan*/  member_3; int /*<<< orphan*/  member_2; TYPE_2__ member_1; TYPE_1__ member_0; } ;

/* Variables and functions */
 scalar_t__ CS46XX_DSP_CAPTURE_CHANNEL ; 
 scalar_t__ DMA_RQ_C1_DEST_MOD1024 ; 
 scalar_t__ DMA_RQ_C1_DEST_ON_HOST ; 
 scalar_t__ DMA_RQ_C1_SOURCE_MOD64 ; 
 scalar_t__ DMA_RQ_C1_WRITEBACK_DEST_FLAG ; 
 scalar_t__ DMA_RQ_C1_WRITEBACK_SRC_FLAG ; 
 scalar_t__ DMA_RQ_C2_AC_NONE ; 
 scalar_t__ DMA_RQ_C2_SIGNAL_DEST_PINGPONG ; 
 scalar_t__ DMA_RQ_SD_SP_SAMPLE_ADDR ; 
 int /*<<< orphan*/  RSCONFIG_DMA_ENABLE ; 
 int RSCONFIG_DMA_TO_HOST ; 
 int RSCONFIG_MAX_DMA_SIZE_SHIFT ; 
 int RSCONFIG_MODULO_64 ; 
 int RSCONFIG_SAMPLE_16STEREO ; 
 int RSCONFIG_STREAM_NUM_SHIFT ; 
 struct dsp_scb_descriptor* cs46xx_dsp_create_generic_scb (struct snd_cs46xx*,char*,int*,int,char*,struct dsp_scb_descriptor*,int) ; 

struct dsp_scb_descriptor * 
cs46xx_dsp_create_mix_to_ostream_scb(struct snd_cs46xx * chip, char * scb_name,
                                     u16 mix_buffer_addr, u16 writeback_spb, u32 dest,
                                     struct dsp_scb_descriptor * parent_scb,
                                     int scb_child_type)
{
	struct dsp_scb_descriptor * scb;

	struct dsp_mix2_ostream_scb mix2_ostream_scb = {
		/* Basic (non scatter/gather) DMA requestor (4 ints) */
		{ 
			DMA_RQ_C1_SOURCE_MOD64 +
			DMA_RQ_C1_DEST_ON_HOST +
			DMA_RQ_C1_DEST_MOD1024 +
			DMA_RQ_C1_WRITEBACK_SRC_FLAG + 
			DMA_RQ_C1_WRITEBACK_DEST_FLAG +
			15,                            
      
			DMA_RQ_C2_AC_NONE +
			DMA_RQ_C2_SIGNAL_DEST_PINGPONG + 
      
			CS46XX_DSP_CAPTURE_CHANNEL,                                 
			DMA_RQ_SD_SP_SAMPLE_ADDR + 
			mix_buffer_addr, 
			0x0                   
		},
    
		{ 0, 0, 0, 0, 0, },
		0,0,
		0,writeback_spb,
    
		RSCONFIG_DMA_ENABLE + 
		(19 << RSCONFIG_MAX_DMA_SIZE_SHIFT) + 
    
		((dest >> 4) << RSCONFIG_STREAM_NUM_SHIFT) +
		RSCONFIG_DMA_TO_HOST + 
		RSCONFIG_SAMPLE_16STEREO +
		RSCONFIG_MODULO_64,    
		(mix_buffer_addr + (32 * 4)) << 0x10,
		1,0,            
		0x0001,0x0080,
		0xFFFF,0
	};


	scb = cs46xx_dsp_create_generic_scb(chip,scb_name,(u32 *)&mix2_ostream_scb,
				
	    dest,"S16_MIX_TO_OSTREAM",parent_scb,
					    scb_child_type);
  
	return scb;
}