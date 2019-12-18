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

/* Variables and functions */
 int AUDREC_CMD_SAMP_RATE_INDX_11025 ; 
 int AUDREC_CMD_SAMP_RATE_INDX_12000 ; 
 int AUDREC_CMD_SAMP_RATE_INDX_16000 ; 
 int AUDREC_CMD_SAMP_RATE_INDX_22050 ; 
 int AUDREC_CMD_SAMP_RATE_INDX_24000 ; 
 int AUDREC_CMD_SAMP_RATE_INDX_32000 ; 
 int AUDREC_CMD_SAMP_RATE_INDX_44100 ; 
 int AUDREC_CMD_SAMP_RATE_INDX_48000 ; 
 int AUDREC_CMD_SAMP_RATE_INDX_8000 ; 

__attribute__((used)) static unsigned convert_dsp_samp_index(unsigned index)
{
	switch (index) {
	case 48000:	return AUDREC_CMD_SAMP_RATE_INDX_48000;
	case 44100:	return AUDREC_CMD_SAMP_RATE_INDX_44100;
	case 32000:	return AUDREC_CMD_SAMP_RATE_INDX_32000;
	case 24000:	return AUDREC_CMD_SAMP_RATE_INDX_24000;
	case 22050:	return AUDREC_CMD_SAMP_RATE_INDX_22050;
	case 16000:	return AUDREC_CMD_SAMP_RATE_INDX_16000;
	case 12000:	return AUDREC_CMD_SAMP_RATE_INDX_12000;
	case 11025:	return AUDREC_CMD_SAMP_RATE_INDX_11025;
	case 8000:	return AUDREC_CMD_SAMP_RATE_INDX_8000;
	default: 	return AUDREC_CMD_SAMP_RATE_INDX_11025;
	}
}