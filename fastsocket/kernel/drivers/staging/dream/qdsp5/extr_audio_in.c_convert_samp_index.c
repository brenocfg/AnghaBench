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
#define  RPC_AUD_DEF_SAMPLE_RATE_11025 136 
#define  RPC_AUD_DEF_SAMPLE_RATE_12000 135 
#define  RPC_AUD_DEF_SAMPLE_RATE_16000 134 
#define  RPC_AUD_DEF_SAMPLE_RATE_22050 133 
#define  RPC_AUD_DEF_SAMPLE_RATE_24000 132 
#define  RPC_AUD_DEF_SAMPLE_RATE_32000 131 
#define  RPC_AUD_DEF_SAMPLE_RATE_44100 130 
#define  RPC_AUD_DEF_SAMPLE_RATE_48000 129 
#define  RPC_AUD_DEF_SAMPLE_RATE_8000 128 

__attribute__((used)) static unsigned convert_samp_index(unsigned index)
{
	switch (index) {
	case RPC_AUD_DEF_SAMPLE_RATE_48000:	return 48000;
	case RPC_AUD_DEF_SAMPLE_RATE_44100:	return 44100;
	case RPC_AUD_DEF_SAMPLE_RATE_32000:	return 32000;
	case RPC_AUD_DEF_SAMPLE_RATE_24000:	return 24000;
	case RPC_AUD_DEF_SAMPLE_RATE_22050:	return 22050;
	case RPC_AUD_DEF_SAMPLE_RATE_16000:	return 16000;
	case RPC_AUD_DEF_SAMPLE_RATE_12000:	return 12000;
	case RPC_AUD_DEF_SAMPLE_RATE_11025:	return 11025;
	case RPC_AUD_DEF_SAMPLE_RATE_8000:	return 8000;
	default: 				return 11025;
	}
}