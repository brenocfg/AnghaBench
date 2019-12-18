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
struct SwsContext {int dummy; } ;
typedef  enum AVPixelFormat { ____Placeholder_AVPixelFormat } AVPixelFormat ;

/* Variables and functions */
 int SWS_FULL_CHR_H_INP ; 
 int SWS_FULL_CHR_H_INT ; 
 int /*<<< orphan*/  av_opt_set_int (struct SwsContext*,char*,int,int /*<<< orphan*/ ) ; 
 int handle_jpeg (int*) ; 
 int /*<<< orphan*/  hb_error (char*) ; 
 struct SwsContext* sws_alloc_context () ; 
 int /*<<< orphan*/  sws_freeContext (struct SwsContext*) ; 
 int /*<<< orphan*/  sws_getCoefficients (int) ; 
 scalar_t__ sws_init_context (struct SwsContext*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sws_setColorspaceDetails (struct SwsContext*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,int) ; 

struct SwsContext*
hb_sws_get_context(int srcW, int srcH, enum AVPixelFormat srcFormat,
                   int dstW, int dstH, enum AVPixelFormat dstFormat,
                   int flags, int colorspace)
{
    struct SwsContext * ctx;

    ctx = sws_alloc_context();
    if ( ctx )
    {
        int srcRange, dstRange;

        srcRange = handle_jpeg(&srcFormat);
        dstRange = handle_jpeg(&dstFormat);
        flags |= SWS_FULL_CHR_H_INT | SWS_FULL_CHR_H_INP;

        av_opt_set_int(ctx, "srcw", srcW, 0);
        av_opt_set_int(ctx, "srch", srcH, 0);
        av_opt_set_int(ctx, "src_range", srcRange, 0);
        av_opt_set_int(ctx, "src_format", srcFormat, 0);
        av_opt_set_int(ctx, "dstw", dstW, 0);
        av_opt_set_int(ctx, "dsth", dstH, 0);
        av_opt_set_int(ctx, "dst_range", dstRange, 0);
        av_opt_set_int(ctx, "dst_format", dstFormat, 0);
        av_opt_set_int(ctx, "sws_flags", flags, 0);

        sws_setColorspaceDetails( ctx,
                      sws_getCoefficients( colorspace ), // src colorspace
                      srcRange, // src range 0 = MPG, 1 = JPG
                      sws_getCoefficients( colorspace ), // dst colorspace
                      dstRange, // dst range 0 = MPG, 1 = JPG
                      0,         // brightness
                      1 << 16,   // contrast
                      1 << 16 ); // saturation

        if (sws_init_context(ctx, NULL, NULL) < 0) {
            hb_error("Cannot initialize resampling context");
            sws_freeContext(ctx);
            ctx = NULL;
        }
    }
    return ctx;
}