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
typedef  int /*<<< orphan*/  speex_quality ;

/* Variables and functions */
 int /*<<< orphan*/  ConfigGetParamBool (int /*<<< orphan*/ ,char*) ; 
 void* ConfigGetParamInt (int /*<<< orphan*/ ,char*) ; 
 char* ConfigGetParamString (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  DebugMessage (int /*<<< orphan*/ ,char*,...) ; 
 void* GameFreq ; 
 int /*<<< orphan*/  M64MSG_WARNING ; 
 void* PrimaryBufferSize ; 
 void* PrimaryBufferTarget ; 
 int /*<<< orphan*/  RESAMPLER_SPEEX ; 
 int /*<<< orphan*/  RESAMPLER_SRC ; 
 int /*<<< orphan*/  RESAMPLER_TRIVIAL ; 
 int /*<<< orphan*/  Resample ; 
 int ResampleQuality ; 
 int SRC_LINEAR ; 
 int SRC_SINC_BEST_QUALITY ; 
 int SRC_SINC_FASTEST ; 
 int SRC_SINC_MEDIUM_QUALITY ; 
 int SRC_ZERO_ORDER_HOLD ; 
 void* SecondaryBufferSize ; 
 int /*<<< orphan*/  SwapChannels ; 
 void* VolDelta ; 
 void* VolPercent ; 
 void* VolumeControlType ; 
 int /*<<< orphan*/  l_ConfigAudio ; 
 scalar_t__ strcmp (char const*,char const*) ; 
 int /*<<< orphan*/  strlen (char*) ; 
 scalar_t__ strncmp (char const*,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ReadConfig(void)
{
    const char *resampler_id;

    /* read the configuration values into our static variables */
    GameFreq = ConfigGetParamInt(l_ConfigAudio, "DEFAULT_FREQUENCY");
    SwapChannels = ConfigGetParamBool(l_ConfigAudio, "SWAP_CHANNELS");
    PrimaryBufferSize = ConfigGetParamInt(l_ConfigAudio, "PRIMARY_BUFFER_SIZE");
    PrimaryBufferTarget = ConfigGetParamInt(l_ConfigAudio, "PRIMARY_BUFFER_TARGET");
    SecondaryBufferSize = ConfigGetParamInt(l_ConfigAudio, "SECONDARY_BUFFER_SIZE");
    resampler_id = ConfigGetParamString(l_ConfigAudio, "RESAMPLE");
    VolumeControlType = ConfigGetParamInt(l_ConfigAudio, "VOLUME_CONTROL_TYPE");
    VolDelta = ConfigGetParamInt(l_ConfigAudio, "VOLUME_ADJUST");
    VolPercent = ConfigGetParamInt(l_ConfigAudio, "VOLUME_DEFAULT");

    if (!resampler_id) {
        Resample = RESAMPLER_TRIVIAL;
	DebugMessage(M64MSG_WARNING, "Could not find RESAMPLE configuration; use trivial resampler");
	return;
    }
    if (strcmp(resampler_id, "trivial") == 0) {
        Resample = RESAMPLER_TRIVIAL;
        return;
    }
#ifdef USE_SPEEX
    if (strncmp(resampler_id, "speex-fixed-", strlen("speex-fixed-")) == 0) {
        int i;
        static const char *speex_quality[] = {
            "speex-fixed-0",
            "speex-fixed-1",
            "speex-fixed-2",
            "speex-fixed-3",
            "speex-fixed-4",
            "speex-fixed-5",
            "speex-fixed-6",
            "speex-fixed-7",
            "speex-fixed-8",
            "speex-fixed-9",
            "speex-fixed-10",
        };
        Resample = RESAMPLER_SPEEX;
        for (i = 0; i < sizeof(speex_quality) / sizeof(*speex_quality); i++) {
            if (strcmp(speex_quality[i], resampler_id) == 0) {
                ResampleQuality = i;
                return;
            }
        }
        DebugMessage(M64MSG_WARNING, "Unknown RESAMPLE configuration %s; use speex-fixed-4 resampler", resampler_id);
        ResampleQuality = 4;
        return;
    }
#endif
#ifdef USE_SRC
    if (strncmp(resampler_id, "src-", strlen("src-")) == 0) {
        Resample = RESAMPLER_SRC;
        if (strcmp(resampler_id, "src-sinc-best-quality") == 0) {
            ResampleQuality = SRC_SINC_BEST_QUALITY;
            return;
        }
        if (strcmp(resampler_id, "src-sinc-medium-quality") == 0) {
            ResampleQuality = SRC_SINC_MEDIUM_QUALITY;
            return;
        }
        if (strcmp(resampler_id, "src-sinc-fastest") == 0) {
            ResampleQuality = SRC_SINC_FASTEST;
            return;
        }
        if (strcmp(resampler_id, "src-zero-order-hold") == 0) {
            ResampleQuality = SRC_ZERO_ORDER_HOLD;
            return;
        }
        if (strcmp(resampler_id, "src-linear") == 0) {
            ResampleQuality = SRC_LINEAR;
            return;
        }
        DebugMessage(M64MSG_WARNING, "Unknown RESAMPLE configuration %s; use src-sinc-medium-quality resampler", resampler_id);
        ResampleQuality = SRC_SINC_MEDIUM_QUALITY;
        return;
    }
#endif
    DebugMessage(M64MSG_WARNING, "Unknown RESAMPLE configuration %s; use trivial resampler", resampler_id);
    Resample = RESAMPLER_TRIVIAL;
}