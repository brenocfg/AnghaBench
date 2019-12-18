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
struct TYPE_3__ {int /*<<< orphan*/  member_1; int /*<<< orphan*/  member_0; } ;
struct dsp_spio_write_scb {TYPE_2__ member_15; int /*<<< orphan*/  member_14; int /*<<< orphan*/  member_13; int /*<<< orphan*/  member_12; int /*<<< orphan*/  member_11; TYPE_1__ member_10; int /*<<< orphan*/  member_9; int /*<<< orphan*/  member_8; int /*<<< orphan*/  member_7; int /*<<< orphan*/  member_6; int /*<<< orphan*/  member_5; int /*<<< orphan*/  member_4; int /*<<< orphan*/  member_3; int /*<<< orphan*/  member_2; int /*<<< orphan*/  member_1; int /*<<< orphan*/  member_0; } ;
struct dsp_scb_descriptor {int dummy; } ;

/* Variables and functions */
 struct dsp_scb_descriptor* cs46xx_dsp_create_generic_scb (struct snd_cs46xx*,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,struct dsp_scb_descriptor*,int) ; 

struct dsp_scb_descriptor * 
cs46xx_dsp_create_spio_write_scb(struct snd_cs46xx * chip, char * scb_name, u32 dest,
                                 struct dsp_scb_descriptor * parent_scb,
                                 int scb_child_type)
{
	struct dsp_scb_descriptor * scb;
  
	struct dsp_spio_write_scb spio_write_scb = {
		0,0,         /*   SPIOWAddress2:SPIOWAddress1; */
		0,           /*   SPIOWData1; */
		0,           /*   SPIOWData2; */
		0,0,         /*   SPIOWAddress4:SPIOWAddress3; */
		0,           /*   SPIOWData3; */
		0,           /*   SPIOWData4; */
		0,0,         /*   SPIOWDataPtr:Unused1; */
		{ 0,0 },     /*   Unused2[2]; */
    
		0,0,	     /*   SPIOWChildPtr:SPIOWSiblingPtr; */
		0,0,         /*   SPIOWThisPtr:SPIOWEntryPoint; */
    
		{ 
			0,
			0,
			0,
			0,
			0          /*   Unused3[5];  */
		}
	};

	scb = cs46xx_dsp_create_generic_scb(chip,scb_name,(u32 *)&spio_write_scb,
					    dest,"SPIOWRITE",parent_scb,
					    scb_child_type);

	return scb;
}