#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  enum AVAudioServiceType { ____Placeholder_AVAudioServiceType } AVAudioServiceType ;
struct TYPE_3__ {int size; scalar_t__ data; } ;
typedef  TYPE_1__ AVPacketSideData ;

/* Variables and functions */
#define  AV_AUDIO_SERVICE_TYPE_COMMENTARY 136 
#define  AV_AUDIO_SERVICE_TYPE_DIALOGUE 135 
#define  AV_AUDIO_SERVICE_TYPE_EFFECTS 134 
#define  AV_AUDIO_SERVICE_TYPE_EMERGENCY 133 
#define  AV_AUDIO_SERVICE_TYPE_HEARING_IMPAIRED 132 
#define  AV_AUDIO_SERVICE_TYPE_KARAOKE 131 
#define  AV_AUDIO_SERVICE_TYPE_MAIN 130 
#define  AV_AUDIO_SERVICE_TYPE_VISUALLY_IMPAIRED 129 
#define  AV_AUDIO_SERVICE_TYPE_VOICE_OVER 128 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  AV_LOG_INFO ; 
 int /*<<< orphan*/  AV_LOG_WARNING ; 
 int /*<<< orphan*/  av_log (void*,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void dump_audioservicetype(void *ctx, AVPacketSideData *sd)
{
    enum AVAudioServiceType *ast = (enum AVAudioServiceType *)sd->data;

    if (sd->size < sizeof(*ast)) {
        av_log(ctx, AV_LOG_ERROR, "invalid data");
        return;
    }

    switch (*ast) {
    case AV_AUDIO_SERVICE_TYPE_MAIN:
        av_log(ctx, AV_LOG_INFO, "main");
        break;
    case AV_AUDIO_SERVICE_TYPE_EFFECTS:
        av_log(ctx, AV_LOG_INFO, "effects");
        break;
    case AV_AUDIO_SERVICE_TYPE_VISUALLY_IMPAIRED:
        av_log(ctx, AV_LOG_INFO, "visually impaired");
        break;
    case AV_AUDIO_SERVICE_TYPE_HEARING_IMPAIRED:
        av_log(ctx, AV_LOG_INFO, "hearing impaired");
        break;
    case AV_AUDIO_SERVICE_TYPE_DIALOGUE:
        av_log(ctx, AV_LOG_INFO, "dialogue");
        break;
    case AV_AUDIO_SERVICE_TYPE_COMMENTARY:
        av_log(ctx, AV_LOG_INFO, "commentary");
        break;
    case AV_AUDIO_SERVICE_TYPE_EMERGENCY:
        av_log(ctx, AV_LOG_INFO, "emergency");
        break;
    case AV_AUDIO_SERVICE_TYPE_VOICE_OVER:
        av_log(ctx, AV_LOG_INFO, "voice over");
        break;
    case AV_AUDIO_SERVICE_TYPE_KARAOKE:
        av_log(ctx, AV_LOG_INFO, "karaoke");
        break;
    default:
        av_log(ctx, AV_LOG_WARNING, "unknown");
        break;
    }
}