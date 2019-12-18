#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct msm_audio_aac_config {scalar_t__ format; scalar_t__ audio_object; int ep_config; scalar_t__ aac_scalefactor_data_resilience_flag; scalar_t__ aac_section_data_resilience_flag; scalar_t__ aac_spectral_data_resilience_flag; scalar_t__ sbr_on_flag; scalar_t__ sbr_ps_on_flag; scalar_t__ dual_mono_mode; int channel_configuration; } ;

/* Variables and functions */
 scalar_t__ AUDIO_AAC_DUAL_MONO_PL_SR ; 
 scalar_t__ AUDIO_AAC_FORMAT_ADTS ; 
 scalar_t__ AUDIO_AAC_FORMAT_LOAS ; 
 scalar_t__ AUDIO_AAC_FORMAT_PSUEDO_RAW ; 
 scalar_t__ AUDIO_AAC_FORMAT_RAW ; 
 scalar_t__ AUDIO_AAC_OBJECT_ERLC ; 
 scalar_t__ AUDIO_AAC_OBJECT_LC ; 
 scalar_t__ AUDIO_AAC_OBJECT_LTP ; 
 scalar_t__ AUDIO_AAC_SBR_ON_FLAG_OFF ; 
 scalar_t__ AUDIO_AAC_SBR_ON_FLAG_ON ; 
 scalar_t__ AUDIO_AAC_SBR_PS_ON_FLAG_OFF ; 
 scalar_t__ AUDIO_AAC_SBR_PS_ON_FLAG_ON ; 
 scalar_t__ AUDIO_AAC_SCA_DATA_RES_OFF ; 
 scalar_t__ AUDIO_AAC_SCA_DATA_RES_ON ; 
 scalar_t__ AUDIO_AAC_SEC_DATA_RES_OFF ; 
 scalar_t__ AUDIO_AAC_SEC_DATA_RES_ON ; 
 scalar_t__ AUDIO_AAC_SPEC_DATA_RES_OFF ; 
 scalar_t__ AUDIO_AAC_SPEC_DATA_RES_ON ; 

__attribute__((used)) static int audaac_validate_usr_config(struct msm_audio_aac_config *config)
{
	int ret_val = -1;

	if (config->format != AUDIO_AAC_FORMAT_ADTS &&
		config->format != AUDIO_AAC_FORMAT_RAW &&
		config->format != AUDIO_AAC_FORMAT_PSUEDO_RAW &&
		config->format != AUDIO_AAC_FORMAT_LOAS)
		goto done;

	if (config->audio_object != AUDIO_AAC_OBJECT_LC &&
		config->audio_object != AUDIO_AAC_OBJECT_LTP &&
		config->audio_object != AUDIO_AAC_OBJECT_ERLC)
		goto done;

	if (config->audio_object == AUDIO_AAC_OBJECT_ERLC) {
		if (config->ep_config > 3)
			goto done;
		if (config->aac_scalefactor_data_resilience_flag !=
			AUDIO_AAC_SCA_DATA_RES_OFF &&
			config->aac_scalefactor_data_resilience_flag !=
			AUDIO_AAC_SCA_DATA_RES_ON)
			goto done;
		if (config->aac_section_data_resilience_flag !=
			AUDIO_AAC_SEC_DATA_RES_OFF &&
			config->aac_section_data_resilience_flag !=
			AUDIO_AAC_SEC_DATA_RES_ON)
			goto done;
		if (config->aac_spectral_data_resilience_flag !=
			AUDIO_AAC_SPEC_DATA_RES_OFF &&
			config->aac_spectral_data_resilience_flag !=
			AUDIO_AAC_SPEC_DATA_RES_ON)
			goto done;
	} else {
		config->aac_section_data_resilience_flag =
			AUDIO_AAC_SEC_DATA_RES_OFF;
		config->aac_scalefactor_data_resilience_flag =
			AUDIO_AAC_SCA_DATA_RES_OFF;
		config->aac_spectral_data_resilience_flag =
			AUDIO_AAC_SPEC_DATA_RES_OFF;
	}

	if (config->sbr_on_flag != AUDIO_AAC_SBR_ON_FLAG_OFF &&
		config->sbr_on_flag != AUDIO_AAC_SBR_ON_FLAG_ON)
		goto done;

	if (config->sbr_ps_on_flag != AUDIO_AAC_SBR_PS_ON_FLAG_OFF &&
		config->sbr_ps_on_flag != AUDIO_AAC_SBR_PS_ON_FLAG_ON)
		goto done;

	if (config->dual_mono_mode > AUDIO_AAC_DUAL_MONO_PL_SR)
		goto done;

	if (config->channel_configuration > 2)
		goto done;

	ret_val = 0;
 done:
	return ret_val;
}