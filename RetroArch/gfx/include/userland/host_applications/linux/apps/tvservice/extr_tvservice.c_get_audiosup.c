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
typedef  int uint8_t ;

/* Variables and functions */
 int EDID_AudioFormat_eMaxCount ; 
 int EDID_AudioFormat_ePCM ; 
 int EDID_AudioSampleRate_e192KHz ; 
 int EDID_AudioSampleRate_e32KHz ; 
 int EDID_AudioSampleRate_e44KHz ; 
 int EDID_AudioSampleSize_16bit ; 
 int EDID_AudioSampleSize_24bit ; 
 int /*<<< orphan*/  LOG_STD (char*,char const*,int,int,int) ; 
 scalar_t__ vc_tv_hdmi_audio_supported (int,int,int,int) ; 

__attribute__((used)) static int get_audiosup( void )
{
  uint8_t sample_rates[] = {32, 44, 48, 88, 96, 176, 192};
  uint8_t sample_sizes[] = {16, 20, 24};
  const char *formats[] = {"Reserved", "PCM", "AC3", "MPEG1", "MP3", "MPEG2", "AAC", "DTS", "ATRAC", "DSD", "EAC3", "DTS_HD", "MLP", "DST", "WMAPRO", "Extended"};
  int i, j, k;
  for (k=EDID_AudioFormat_ePCM; k<EDID_AudioFormat_eMaxCount; k++) {
    int num_channels = 0, max_sample_rate = 0, max_sample_size = 0;
    for (i=1; i<=8; i++) {
      if (vc_tv_hdmi_audio_supported(k, i, EDID_AudioSampleRate_e44KHz, EDID_AudioSampleSize_16bit ) == 0)
        num_channels = i;
    }
    for (i=0, j=EDID_AudioSampleRate_e32KHz; j<=EDID_AudioSampleRate_e192KHz; i++, j<<=1) {
      if (vc_tv_hdmi_audio_supported(k, 1, j, EDID_AudioSampleSize_16bit ) == 0)
        max_sample_rate = i;
    }
    if (k==EDID_AudioFormat_ePCM) {
      for (i=0, j=EDID_AudioSampleSize_16bit; j<=EDID_AudioSampleSize_24bit; i++, j<<=1) {
        if (vc_tv_hdmi_audio_supported(k, 1, EDID_AudioSampleRate_e44KHz, j ) == 0)
          max_sample_size = i;
      }
      if (num_channels>0)
        LOG_STD("%8s supported: Max channels: %d, Max samplerate:%4dkHz, Max samplesize %2d bits.", formats[k], num_channels, sample_rates[max_sample_rate], sample_sizes[max_sample_size]);
    } else {
      for (i=0; i<256; i++) {
        if (vc_tv_hdmi_audio_supported(k, 1, EDID_AudioSampleRate_e44KHz, i ) == 0)
          max_sample_size = i;
      }
      if (num_channels>0)
        LOG_STD("%8s supported: Max channels: %d, Max samplerate:%4dkHz, Max rate %4d kb/s.", formats[k], num_channels, sample_rates[max_sample_rate], 8*max_sample_size);
    }
  }
  return 0;
}