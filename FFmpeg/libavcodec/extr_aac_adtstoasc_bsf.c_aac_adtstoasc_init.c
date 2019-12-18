#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {TYPE_1__* par_in; } ;
struct TYPE_6__ {int /*<<< orphan*/  extradata_size; scalar_t__ extradata; } ;
typedef  int /*<<< orphan*/  MPEG4AudioConfig ;
typedef  TYPE_2__ AVBSFContext ;

/* Variables and functions */
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  av_log (TYPE_2__*,int /*<<< orphan*/ ,char*) ; 
 int avpriv_mpeg4audio_get_config2 (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ,int,TYPE_2__*) ; 

__attribute__((used)) static int aac_adtstoasc_init(AVBSFContext *ctx)
{
    /* Validate the extradata if the stream is already MPEG-4 AudioSpecificConfig */
    if (ctx->par_in->extradata) {
        MPEG4AudioConfig mp4ac;
        int ret = avpriv_mpeg4audio_get_config2(&mp4ac, ctx->par_in->extradata,
                                                ctx->par_in->extradata_size, 1, ctx);
        if (ret < 0) {
            av_log(ctx, AV_LOG_ERROR, "Error parsing AudioSpecificConfig extradata!\n");
            return ret;
        }
    }

    return 0;
}