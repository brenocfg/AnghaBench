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
 int RPC_AUD_DEF_SAMPLE_RATE_11025 ; 
 int RPC_AUD_DEF_SAMPLE_RATE_12000 ; 
 int RPC_AUD_DEF_SAMPLE_RATE_16000 ; 
 int RPC_AUD_DEF_SAMPLE_RATE_22050 ; 
 int RPC_AUD_DEF_SAMPLE_RATE_24000 ; 
 int RPC_AUD_DEF_SAMPLE_RATE_32000 ; 
 int RPC_AUD_DEF_SAMPLE_RATE_44100 ; 
 int RPC_AUD_DEF_SAMPLE_RATE_48000 ; 
 int RPC_AUD_DEF_SAMPLE_RATE_8000 ; 

__attribute__((used)) static unsigned convert_samp_rate(unsigned hz)
{
	switch (hz) {
	case 48000: return RPC_AUD_DEF_SAMPLE_RATE_48000;
	case 44100: return RPC_AUD_DEF_SAMPLE_RATE_44100;
	case 32000: return RPC_AUD_DEF_SAMPLE_RATE_32000;
	case 24000: return RPC_AUD_DEF_SAMPLE_RATE_24000;
	case 22050: return RPC_AUD_DEF_SAMPLE_RATE_22050;
	case 16000: return RPC_AUD_DEF_SAMPLE_RATE_16000;
	case 12000: return RPC_AUD_DEF_SAMPLE_RATE_12000;
	case 11025: return RPC_AUD_DEF_SAMPLE_RATE_11025;
	case 8000:  return RPC_AUD_DEF_SAMPLE_RATE_8000;
	default:    return RPC_AUD_DEF_SAMPLE_RATE_11025;
	}
}