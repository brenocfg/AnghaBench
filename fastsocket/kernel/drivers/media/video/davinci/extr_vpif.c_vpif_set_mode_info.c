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
typedef  size_t u8 ;
typedef  int u32 ;
struct vpif_channel_config_params {int eav2sav; int sav2eav; int l1; int l3; int l5; int l7; int l9; int l11; int vsize; } ;
struct TYPE_2__ {int width_mask; int len_mask; int /*<<< orphan*/  v_cfg; int /*<<< orphan*/  v_cfg_02; int /*<<< orphan*/  v_cfg_01; int /*<<< orphan*/  v_cfg_00; int /*<<< orphan*/  h_cfg; } ;

/* Variables and functions */
 int VPIF_CH_LEN_SHIFT ; 
 int /*<<< orphan*/  regw (int,int /*<<< orphan*/ ) ; 
 TYPE_1__* vpifregs ; 

__attribute__((used)) static void vpif_set_mode_info(const struct vpif_channel_config_params *config,
				u8 channel_id, u8 config_channel_id)
{
	u32 value;

	value = (config->eav2sav & vpifregs[config_channel_id].width_mask);
	value <<= VPIF_CH_LEN_SHIFT;
	value |= (config->sav2eav & vpifregs[config_channel_id].width_mask);
	regw(value, vpifregs[channel_id].h_cfg);

	value = (config->l1 & vpifregs[config_channel_id].len_mask);
	value <<= VPIF_CH_LEN_SHIFT;
	value |= (config->l3 & vpifregs[config_channel_id].len_mask);
	regw(value, vpifregs[channel_id].v_cfg_00);

	value = (config->l5 & vpifregs[config_channel_id].len_mask);
	value <<= VPIF_CH_LEN_SHIFT;
	value |= (config->l7 & vpifregs[config_channel_id].len_mask);
	regw(value, vpifregs[channel_id].v_cfg_01);

	value = (config->l9 & vpifregs[config_channel_id].len_mask);
	value <<= VPIF_CH_LEN_SHIFT;
	value |= (config->l11 & vpifregs[config_channel_id].len_mask);
	regw(value, vpifregs[channel_id].v_cfg_02);

	value = (config->vsize & vpifregs[config_channel_id].len_mask);
	regw(value, vpifregs[channel_id].v_cfg);
}