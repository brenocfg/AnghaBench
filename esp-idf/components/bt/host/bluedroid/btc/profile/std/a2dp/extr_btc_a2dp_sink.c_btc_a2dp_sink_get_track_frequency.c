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
typedef  int UINT8 ;

/* Variables and functions */
#define  A2D_SBC_IE_SAMP_FREQ_16 131 
#define  A2D_SBC_IE_SAMP_FREQ_32 130 
#define  A2D_SBC_IE_SAMP_FREQ_44 129 
#define  A2D_SBC_IE_SAMP_FREQ_48 128 

__attribute__((used)) static int btc_a2dp_sink_get_track_frequency(UINT8 frequency)
{
    int freq = 48000;
    switch (frequency) {
    case A2D_SBC_IE_SAMP_FREQ_16:
        freq = 16000;
        break;
    case A2D_SBC_IE_SAMP_FREQ_32:
        freq = 32000;
        break;
    case A2D_SBC_IE_SAMP_FREQ_44:
        freq = 44100;
        break;
    case A2D_SBC_IE_SAMP_FREQ_48:
        freq = 48000;
        break;
    }
    return freq;
}