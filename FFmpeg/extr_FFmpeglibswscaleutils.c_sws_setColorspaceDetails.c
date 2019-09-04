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
struct SwsContext {int srcRange; int dstRange; int brightness; int contrast; int saturation; int const* srcColorspaceTable; int const* dstColorspaceTable; int srcBpc; size_t cascaded_mainindex; int srcW; int srcH; int dstW; int dstH; int /*<<< orphan*/  dstFormat; struct SwsContext** cascaded_context; int /*<<< orphan*/  param; int /*<<< orphan*/  flags; int /*<<< orphan*/  alphablend; int /*<<< orphan*/  srcFormat; int /*<<< orphan*/  cascaded_tmpStride; int /*<<< orphan*/  cascaded_tmp; void* srcFormatBpp; void* dstFormatBpp; } ;
typedef  enum AVPixelFormat { ____Placeholder_AVPixelFormat } AVPixelFormat ;
typedef  int /*<<< orphan*/  AVPixFmtDescriptor ;

/* Variables and functions */
 scalar_t__ ARCH_PPC ; 
 int /*<<< orphan*/  AV_LOG_VERBOSE ; 
 int AV_PIX_FMT_BGR24 ; 
 int AV_PIX_FMT_BGR48 ; 
 int AV_PIX_FMT_BGRA ; 
 int AV_PIX_FMT_BGRA64 ; 
 void* av_get_bits_per_pixel (int /*<<< orphan*/  const*) ; 
 int av_image_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int,int) ; 
 int /*<<< orphan*/  av_log (struct SwsContext*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/ * av_pix_fmt_desc_get (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ff_sws_init_range_convert (struct SwsContext*) ; 
 int /*<<< orphan*/  ff_yuv2rgb_c_init_tables (struct SwsContext*,int const*,int,int,int,int) ; 
 int /*<<< orphan*/  ff_yuv2rgb_init_tables_ppc (struct SwsContext*,int const*,int,int,int) ; 
 int /*<<< orphan*/  fill_rgb2yuv_table (struct SwsContext*,int const*,int) ; 
 int /*<<< orphan*/  handle_formats (struct SwsContext*) ; 
 scalar_t__ is16BPS (int /*<<< orphan*/ ) ; 
 scalar_t__ isALPHA (int /*<<< orphan*/ ) ; 
 scalar_t__ isGray (int /*<<< orphan*/ ) ; 
 scalar_t__ isNBPS (int /*<<< orphan*/ ) ; 
 scalar_t__ isYUV (int /*<<< orphan*/ ) ; 
 scalar_t__ memcmp (int const*,int const*,int) ; 
 int /*<<< orphan*/  memmove (int const*,int const*,int) ; 
 struct SwsContext* sws_alloc_set_opts (int,int,int /*<<< orphan*/ ,int,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct SwsContext* sws_getContext (int,int,int,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int sws_init_context (struct SwsContext*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int sws_setColorspaceDetails(struct SwsContext *c, const int inv_table[4],
                             int srcRange, const int table[4], int dstRange,
                             int brightness, int contrast, int saturation)
{
    const AVPixFmtDescriptor *desc_dst;
    const AVPixFmtDescriptor *desc_src;
    int need_reinit = 0;

    handle_formats(c);
    desc_dst = av_pix_fmt_desc_get(c->dstFormat);
    desc_src = av_pix_fmt_desc_get(c->srcFormat);

    if(!isYUV(c->dstFormat) && !isGray(c->dstFormat))
        dstRange = 0;
    if(!isYUV(c->srcFormat) && !isGray(c->srcFormat))
        srcRange = 0;

    if (c->srcRange != srcRange ||
        c->dstRange != dstRange ||
        c->brightness != brightness ||
        c->contrast   != contrast ||
        c->saturation != saturation ||
        memcmp(c->srcColorspaceTable, inv_table, sizeof(int) * 4) ||
        memcmp(c->dstColorspaceTable,     table, sizeof(int) * 4)
    )
        need_reinit = 1;

    memmove(c->srcColorspaceTable, inv_table, sizeof(int) * 4);
    memmove(c->dstColorspaceTable, table, sizeof(int) * 4);



    c->brightness = brightness;
    c->contrast   = contrast;
    c->saturation = saturation;
    c->srcRange   = srcRange;
    c->dstRange   = dstRange;

    //The srcBpc check is possibly wrong but we seem to lack a definitive reference to test this
    //and what we have in ticket 2939 looks better with this check
    if (need_reinit && (c->srcBpc == 8 || !isYUV(c->srcFormat)))
        ff_sws_init_range_convert(c);

    c->dstFormatBpp = av_get_bits_per_pixel(desc_dst);
    c->srcFormatBpp = av_get_bits_per_pixel(desc_src);

    if (c->cascaded_context[c->cascaded_mainindex])
        return sws_setColorspaceDetails(c->cascaded_context[c->cascaded_mainindex],inv_table, srcRange,table, dstRange, brightness,  contrast, saturation);

    if (!need_reinit)
        return 0;

    if ((isYUV(c->dstFormat) || isGray(c->dstFormat)) && (isYUV(c->srcFormat) || isGray(c->srcFormat))) {
        if (!c->cascaded_context[0] &&
            memcmp(c->dstColorspaceTable, c->srcColorspaceTable, sizeof(int) * 4) &&
            c->srcW && c->srcH && c->dstW && c->dstH) {
            enum AVPixelFormat tmp_format;
            int tmp_width, tmp_height;
            int srcW = c->srcW;
            int srcH = c->srcH;
            int dstW = c->dstW;
            int dstH = c->dstH;
            int ret;
            av_log(c, AV_LOG_VERBOSE, "YUV color matrix differs for YUV->YUV, using intermediate RGB to convert\n");

            if (isNBPS(c->dstFormat) || is16BPS(c->dstFormat)) {
                if (isALPHA(c->srcFormat) && isALPHA(c->dstFormat)) {
                    tmp_format = AV_PIX_FMT_BGRA64;
                } else {
                    tmp_format = AV_PIX_FMT_BGR48;
                }
            } else {
                if (isALPHA(c->srcFormat) && isALPHA(c->dstFormat)) {
                    tmp_format = AV_PIX_FMT_BGRA;
                } else {
                    tmp_format = AV_PIX_FMT_BGR24;
                }
            }

            if (srcW*srcH > dstW*dstH) {
                tmp_width  = dstW;
                tmp_height = dstH;
            } else {
                tmp_width  = srcW;
                tmp_height = srcH;
            }

            ret = av_image_alloc(c->cascaded_tmp, c->cascaded_tmpStride,
                                tmp_width, tmp_height, tmp_format, 64);
            if (ret < 0)
                return ret;

            c->cascaded_context[0] = sws_alloc_set_opts(srcW, srcH, c->srcFormat,
                                                        tmp_width, tmp_height, tmp_format,
                                                        c->flags, c->param);
            if (!c->cascaded_context[0])
                return -1;

            c->cascaded_context[0]->alphablend = c->alphablend;
            ret = sws_init_context(c->cascaded_context[0], NULL , NULL);
            if (ret < 0)
                return ret;
            //we set both src and dst depending on that the RGB side will be ignored
            sws_setColorspaceDetails(c->cascaded_context[0], inv_table,
                                     srcRange, table, dstRange,
                                     brightness, contrast, saturation);

            c->cascaded_context[1] = sws_getContext(tmp_width, tmp_height, tmp_format,
                                                    dstW, dstH, c->dstFormat,
                                                    c->flags, NULL, NULL, c->param);
            if (!c->cascaded_context[1])
                return -1;
            sws_setColorspaceDetails(c->cascaded_context[1], inv_table,
                                     srcRange, table, dstRange,
                                     0, 1 << 16, 1 << 16);
            return 0;
        }
        return -1;
    }

    if (!isYUV(c->dstFormat) && !isGray(c->dstFormat)) {
        ff_yuv2rgb_c_init_tables(c, inv_table, srcRange, brightness,
                                 contrast, saturation);
        // FIXME factorize

        if (ARCH_PPC)
            ff_yuv2rgb_init_tables_ppc(c, inv_table, brightness,
                                       contrast, saturation);
    }

    fill_rgb2yuv_table(c, table, dstRange);

    return 0;
}