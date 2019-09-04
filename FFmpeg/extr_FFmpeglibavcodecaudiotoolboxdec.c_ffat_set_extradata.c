#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  UInt32 ;
struct TYPE_8__ {int /*<<< orphan*/ * extradata; int /*<<< orphan*/  converter; } ;
struct TYPE_7__ {TYPE_2__* priv_data; } ;
typedef  scalar_t__ OSStatus ;
typedef  TYPE_1__ AVCodecContext ;
typedef  TYPE_2__ ATDecodeContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AV_LOG_WARNING ; 
 scalar_t__ AudioConverterSetProperty (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  av_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  av_log (TYPE_1__*,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/ * ffat_get_magic_cookie (TYPE_1__*,int /*<<< orphan*/ *) ; 
 scalar_t__ ffat_usable_extradata (TYPE_1__*) ; 
 int /*<<< orphan*/  kAudioConverterDecompressionMagicCookie ; 

__attribute__((used)) static int ffat_set_extradata(AVCodecContext *avctx)
{
    ATDecodeContext *at = avctx->priv_data;
    if (ffat_usable_extradata(avctx)) {
        OSStatus status;
        UInt32 cookie_size;
        uint8_t *cookie = ffat_get_magic_cookie(avctx, &cookie_size);
        if (!cookie)
            return AVERROR(ENOMEM);

        status = AudioConverterSetProperty(at->converter,
                                           kAudioConverterDecompressionMagicCookie,
                                           cookie_size, cookie);
        if (status != 0)
            av_log(avctx, AV_LOG_WARNING, "AudioToolbox cookie error: %i\n", (int)status);

        if (cookie != at->extradata)
            av_free(cookie);
    }
    return 0;
}