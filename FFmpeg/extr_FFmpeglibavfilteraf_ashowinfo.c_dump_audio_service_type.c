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
typedef  TYPE_1__ AVFrameSideData ;
typedef  int /*<<< orphan*/  AVFilterContext ;

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
 int /*<<< orphan*/  AV_LOG_INFO ; 
 int /*<<< orphan*/  av_log (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void dump_audio_service_type(AVFilterContext *ctx, AVFrameSideData *sd)
{
    enum AVAudioServiceType *ast;

    av_log(ctx, AV_LOG_INFO, "audio service type: ");
    if (sd->size < sizeof(*ast)) {
        av_log(ctx, AV_LOG_INFO, "invalid data");
        return;
    }
    ast = (enum AVAudioServiceType*)sd->data;
    switch (*ast) {
    case AV_AUDIO_SERVICE_TYPE_MAIN:              av_log(ctx, AV_LOG_INFO, "Main Audio Service"); break;
    case AV_AUDIO_SERVICE_TYPE_EFFECTS:           av_log(ctx, AV_LOG_INFO, "Effects");            break;
    case AV_AUDIO_SERVICE_TYPE_VISUALLY_IMPAIRED: av_log(ctx, AV_LOG_INFO, "Visually Impaired");  break;
    case AV_AUDIO_SERVICE_TYPE_HEARING_IMPAIRED:  av_log(ctx, AV_LOG_INFO, "Hearing Impaired");   break;
    case AV_AUDIO_SERVICE_TYPE_DIALOGUE:          av_log(ctx, AV_LOG_INFO, "Dialogue");           break;
    case AV_AUDIO_SERVICE_TYPE_COMMENTARY:        av_log(ctx, AV_LOG_INFO, "Commentary");         break;
    case AV_AUDIO_SERVICE_TYPE_EMERGENCY:         av_log(ctx, AV_LOG_INFO, "Emergency");          break;
    case AV_AUDIO_SERVICE_TYPE_VOICE_OVER:        av_log(ctx, AV_LOG_INFO, "Voice Over");         break;
    case AV_AUDIO_SERVICE_TYPE_KARAOKE:           av_log(ctx, AV_LOG_INFO, "Karaoke");            break;
    default:                                      av_log(ctx, AV_LOG_INFO, "unknown");            break;
    }
}