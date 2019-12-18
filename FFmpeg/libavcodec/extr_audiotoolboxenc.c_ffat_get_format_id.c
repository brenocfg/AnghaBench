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
typedef  enum AVCodecID { ____Placeholder_AVCodecID } AVCodecID ;
typedef  int /*<<< orphan*/  UInt32 ;

/* Variables and functions */
#define  AV_CODEC_ID_AAC 138 
#define  AV_CODEC_ID_ADPCM_IMA_QT 137 
#define  AV_CODEC_ID_ALAC 136 
#define  AV_CODEC_ID_ILBC 135 
#define  AV_CODEC_ID_PCM_ALAW 134 
#define  AV_CODEC_ID_PCM_MULAW 133 
#define  FF_PROFILE_AAC_ELD 132 
#define  FF_PROFILE_AAC_HE 131 
#define  FF_PROFILE_AAC_HE_V2 130 
#define  FF_PROFILE_AAC_LD 129 
#define  FF_PROFILE_AAC_LOW 128 
 int /*<<< orphan*/  av_assert0 (int) ; 
 int /*<<< orphan*/  kAudioFormatALaw ; 
 int /*<<< orphan*/  kAudioFormatAppleIMA4 ; 
 int /*<<< orphan*/  kAudioFormatAppleLossless ; 
 int /*<<< orphan*/  kAudioFormatMPEG4AAC ; 
 int /*<<< orphan*/  kAudioFormatMPEG4AAC_ELD ; 
 int /*<<< orphan*/  kAudioFormatMPEG4AAC_HE ; 
 int /*<<< orphan*/  kAudioFormatMPEG4AAC_HE_V2 ; 
 int /*<<< orphan*/  kAudioFormatMPEG4AAC_LD ; 
 int /*<<< orphan*/  kAudioFormatULaw ; 
 int /*<<< orphan*/  kAudioFormatiLBC ; 

__attribute__((used)) static UInt32 ffat_get_format_id(enum AVCodecID codec, int profile)
{
    switch (codec) {
    case AV_CODEC_ID_AAC:
        switch (profile) {
        case FF_PROFILE_AAC_LOW:
        default:
            return kAudioFormatMPEG4AAC;
        case FF_PROFILE_AAC_HE:
            return kAudioFormatMPEG4AAC_HE;
        case FF_PROFILE_AAC_HE_V2:
            return kAudioFormatMPEG4AAC_HE_V2;
        case FF_PROFILE_AAC_LD:
            return kAudioFormatMPEG4AAC_LD;
        case FF_PROFILE_AAC_ELD:
            return kAudioFormatMPEG4AAC_ELD;
        }
    case AV_CODEC_ID_ADPCM_IMA_QT:
        return kAudioFormatAppleIMA4;
    case AV_CODEC_ID_ALAC:
        return kAudioFormatAppleLossless;
    case AV_CODEC_ID_ILBC:
        return kAudioFormatiLBC;
    case AV_CODEC_ID_PCM_ALAW:
        return kAudioFormatALaw;
    case AV_CODEC_ID_PCM_MULAW:
        return kAudioFormatULaw;
    default:
        av_assert0(!"Invalid codec ID!");
        return 0;
    }
}