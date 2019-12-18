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
#define  AV_CODEC_ID_AAC 142 
#define  AV_CODEC_ID_AC3 141 
#define  AV_CODEC_ID_ADPCM_IMA_QT 140 
#define  AV_CODEC_ID_ALAC 139 
#define  AV_CODEC_ID_AMR_NB 138 
#define  AV_CODEC_ID_EAC3 137 
#define  AV_CODEC_ID_GSM_MS 136 
#define  AV_CODEC_ID_ILBC 135 
#define  AV_CODEC_ID_MP1 134 
#define  AV_CODEC_ID_MP2 133 
#define  AV_CODEC_ID_MP3 132 
#define  AV_CODEC_ID_PCM_ALAW 131 
#define  AV_CODEC_ID_PCM_MULAW 130 
#define  AV_CODEC_ID_QDM2 129 
#define  AV_CODEC_ID_QDMC 128 
 int /*<<< orphan*/  av_assert0 (int) ; 
 int /*<<< orphan*/  kAudioFormatAC3 ; 
 int /*<<< orphan*/  kAudioFormatALaw ; 
 int /*<<< orphan*/  kAudioFormatAMR ; 
 int /*<<< orphan*/  kAudioFormatAppleIMA4 ; 
 int /*<<< orphan*/  kAudioFormatAppleLossless ; 
 int /*<<< orphan*/  kAudioFormatEnhancedAC3 ; 
 int /*<<< orphan*/  kAudioFormatMPEG4AAC ; 
 int /*<<< orphan*/  kAudioFormatMPEGLayer1 ; 
 int /*<<< orphan*/  kAudioFormatMPEGLayer2 ; 
 int /*<<< orphan*/  kAudioFormatMPEGLayer3 ; 
 int /*<<< orphan*/  kAudioFormatMicrosoftGSM ; 
 int /*<<< orphan*/  kAudioFormatQDesign ; 
 int /*<<< orphan*/  kAudioFormatQDesign2 ; 
 int /*<<< orphan*/  kAudioFormatULaw ; 
 int /*<<< orphan*/  kAudioFormatiLBC ; 

__attribute__((used)) static UInt32 ffat_get_format_id(enum AVCodecID codec, int profile)
{
    switch (codec) {
    case AV_CODEC_ID_AAC:
        return kAudioFormatMPEG4AAC;
    case AV_CODEC_ID_AC3:
        return kAudioFormatAC3;
    case AV_CODEC_ID_ADPCM_IMA_QT:
        return kAudioFormatAppleIMA4;
    case AV_CODEC_ID_ALAC:
        return kAudioFormatAppleLossless;
    case AV_CODEC_ID_AMR_NB:
        return kAudioFormatAMR;
    case AV_CODEC_ID_EAC3:
        return kAudioFormatEnhancedAC3;
    case AV_CODEC_ID_GSM_MS:
        return kAudioFormatMicrosoftGSM;
    case AV_CODEC_ID_ILBC:
        return kAudioFormatiLBC;
    case AV_CODEC_ID_MP1:
        return kAudioFormatMPEGLayer1;
    case AV_CODEC_ID_MP2:
        return kAudioFormatMPEGLayer2;
    case AV_CODEC_ID_MP3:
        return kAudioFormatMPEGLayer3;
    case AV_CODEC_ID_PCM_ALAW:
        return kAudioFormatALaw;
    case AV_CODEC_ID_PCM_MULAW:
        return kAudioFormatULaw;
    case AV_CODEC_ID_QDMC:
        return kAudioFormatQDesign;
    case AV_CODEC_ID_QDM2:
        return kAudioFormatQDesign2;
    default:
        av_assert0(!"Invalid codec ID!");
        return 0;
    }
}