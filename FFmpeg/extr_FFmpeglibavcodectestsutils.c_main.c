#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ type; int /*<<< orphan*/  name; int /*<<< orphan*/  sample_fmts; } ;
typedef  TYPE_1__ AVCodec ;

/* Variables and functions */
 scalar_t__ AVMEDIA_TYPE_AUDIO ; 
 int /*<<< orphan*/  AV_LOG_FATAL ; 
 scalar_t__ av_codec_is_encoder (TYPE_1__*) ; 
 TYPE_1__* av_codec_next (TYPE_1__*) ; 
 int /*<<< orphan*/  av_log (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

int main(void){
    AVCodec *codec = NULL;
    int ret = 0;

    while (codec = av_codec_next(codec)) {
        if (av_codec_is_encoder(codec)) {
            if (codec->type == AVMEDIA_TYPE_AUDIO) {
                if (!codec->sample_fmts) {
                    av_log(NULL, AV_LOG_FATAL, "Encoder %s is missing the sample_fmts field\n", codec->name);
                    ret = 1;
                }
            }
        }
    }
    return ret;
}