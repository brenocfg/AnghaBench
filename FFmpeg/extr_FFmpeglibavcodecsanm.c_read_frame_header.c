#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ width; scalar_t__ height; void* rle_output_size; void* bg_color; void* rotate_code; void* codec; void* seq_num; } ;
struct TYPE_5__ {scalar_t__ width; scalar_t__ height; int /*<<< orphan*/  gb; void** codebook; void** small_codebook; int /*<<< orphan*/  avctx; } ;
typedef  TYPE_1__ SANMVideoContext ;
typedef  TYPE_2__ SANMFrameHeader ;

/* Variables and functions */
 int AVERROR_INVALIDDATA ; 
 int AVERROR_PATCHWELCOME ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  av_log (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  avpriv_report_missing_feature (int /*<<< orphan*/ ,char*) ; 
 int bytestream2_get_bytes_left (int /*<<< orphan*/ *) ; 
 void* bytestream2_get_byteu (int /*<<< orphan*/ *) ; 
 void* bytestream2_get_le16u (int /*<<< orphan*/ *) ; 
 void* bytestream2_get_le32u (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bytestream2_skip (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int read_frame_header(SANMVideoContext *ctx, SANMFrameHeader *hdr)
{
    int i, ret;

    if ((ret = bytestream2_get_bytes_left(&ctx->gb)) < 560) {
        av_log(ctx->avctx, AV_LOG_ERROR, "Input frame too short (%d bytes).\n",
               ret);
        return AVERROR_INVALIDDATA;
    }
    bytestream2_skip(&ctx->gb, 8); // skip pad

    hdr->width  = bytestream2_get_le32u(&ctx->gb);
    hdr->height = bytestream2_get_le32u(&ctx->gb);

    if (hdr->width != ctx->width || hdr->height != ctx->height) {
        avpriv_report_missing_feature(ctx->avctx, "Variable size frames");
        return AVERROR_PATCHWELCOME;
    }

    hdr->seq_num     = bytestream2_get_le16u(&ctx->gb);
    hdr->codec       = bytestream2_get_byteu(&ctx->gb);
    hdr->rotate_code = bytestream2_get_byteu(&ctx->gb);

    bytestream2_skip(&ctx->gb, 4); // skip pad

    for (i = 0; i < 4; i++)
        ctx->small_codebook[i] = bytestream2_get_le16u(&ctx->gb);
    hdr->bg_color = bytestream2_get_le16u(&ctx->gb);

    bytestream2_skip(&ctx->gb, 2); // skip pad

    hdr->rle_output_size = bytestream2_get_le32u(&ctx->gb);
    for (i = 0; i < 256; i++)
        ctx->codebook[i] = bytestream2_get_le16u(&ctx->gb);

    bytestream2_skip(&ctx->gb, 8); // skip pad

    return 0;
}