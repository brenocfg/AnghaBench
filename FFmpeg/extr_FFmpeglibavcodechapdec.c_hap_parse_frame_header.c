#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ int64_t ;
typedef  enum HapSectionType { ____Placeholder_HapSectionType } HapSectionType ;
struct TYPE_16__ {scalar_t__ codec_tag; TYPE_1__* priv_data; } ;
struct TYPE_15__ {scalar_t__ buffer; } ;
struct TYPE_14__ {int compressor; scalar_t__ compressed_offset; int compressed_size; scalar_t__ uncompressed_offset; scalar_t__ uncompressed_size; } ;
struct TYPE_13__ {int texture_section_size; scalar_t__ tex_size; int chunk_count; TYPE_2__* chunks; TYPE_3__ gbc; } ;
typedef  TYPE_1__ HapContext ;
typedef  TYPE_2__ HapChunk ;
typedef  TYPE_3__ GetByteContext ;
typedef  TYPE_4__ AVCodecContext ;

/* Variables and functions */
 int AVERROR_INVALIDDATA ; 
 int /*<<< orphan*/  AV_LOG_DEBUG ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
#define  HAP_COMP_COMPLEX 130 
#define  HAP_COMP_NONE 129 
#define  HAP_COMP_SNAPPY 128 
 int HAP_FMT_RGBADXT5 ; 
 int HAP_FMT_RGBDXT1 ; 
 int HAP_FMT_RGTC1 ; 
 int HAP_FMT_YCOCGDXT5 ; 
 int HAP_ST_DECODE_INSTRUCTIONS ; 
 scalar_t__ MKTAG (char,char,char,char) ; 
 int /*<<< orphan*/  av_log (TYPE_4__*,int /*<<< orphan*/ ,char*,...) ; 
 scalar_t__ bytestream2_get_bytes_left (TYPE_3__*) ; 
 int /*<<< orphan*/  bytestream2_init (TYPE_3__*,scalar_t__,scalar_t__) ; 
 int ff_hap_parse_section_header (TYPE_3__*,int*,int*) ; 
 int ff_hap_set_chunk_count (TYPE_1__*,int,int) ; 
 scalar_t__ ff_snappy_peek_uncompressed_length (TYPE_3__*) ; 
 int hap_parse_decode_instructions (TYPE_1__*,int) ; 

__attribute__((used)) static int hap_parse_frame_header(AVCodecContext *avctx)
{
    HapContext *ctx = avctx->priv_data;
    GetByteContext *gbc = &ctx->gbc;
    int section_size;
    enum HapSectionType section_type;
    const char *compressorstr;
    int i, ret;

    ret = ff_hap_parse_section_header(gbc, &ctx->texture_section_size, &section_type);
    if (ret != 0)
        return ret;

    if ((avctx->codec_tag == MKTAG('H','a','p','1') && (section_type & 0x0F) != HAP_FMT_RGBDXT1) ||
        (avctx->codec_tag == MKTAG('H','a','p','5') && (section_type & 0x0F) != HAP_FMT_RGBADXT5) ||
        (avctx->codec_tag == MKTAG('H','a','p','Y') && (section_type & 0x0F) != HAP_FMT_YCOCGDXT5) ||
        (avctx->codec_tag == MKTAG('H','a','p','A') && (section_type & 0x0F) != HAP_FMT_RGTC1) ||
        ((avctx->codec_tag == MKTAG('H','a','p','M') && (section_type & 0x0F) != HAP_FMT_RGTC1) &&
                                                        (section_type & 0x0F) != HAP_FMT_YCOCGDXT5)) {
        av_log(avctx, AV_LOG_ERROR,
               "Invalid texture format %#04x.\n", section_type & 0x0F);
        return AVERROR_INVALIDDATA;
    }

    switch (section_type & 0xF0) {
        case HAP_COMP_NONE:
        case HAP_COMP_SNAPPY:
            ret = ff_hap_set_chunk_count(ctx, 1, 1);
            if (ret == 0) {
                ctx->chunks[0].compressor = section_type & 0xF0;
                ctx->chunks[0].compressed_offset = 0;
                ctx->chunks[0].compressed_size = ctx->texture_section_size;
            }
            if (ctx->chunks[0].compressor == HAP_COMP_NONE) {
                compressorstr = "none";
            } else {
                compressorstr = "snappy";
            }
            break;
        case HAP_COMP_COMPLEX:
            ret = ff_hap_parse_section_header(gbc, &section_size, &section_type);
            if (ret == 0 && section_type != HAP_ST_DECODE_INSTRUCTIONS)
                ret = AVERROR_INVALIDDATA;
            if (ret == 0)
                ret = hap_parse_decode_instructions(ctx, section_size);
            compressorstr = "complex";
            break;
        default:
            ret = AVERROR_INVALIDDATA;
            break;
    }

    if (ret != 0)
        return ret;

    /* Check the frame is valid and read the uncompressed chunk sizes */
    ctx->tex_size = 0;
    for (i = 0; i < ctx->chunk_count; i++) {
        HapChunk *chunk = &ctx->chunks[i];

        /* Check the compressed buffer is valid */
        if (chunk->compressed_offset + chunk->compressed_size > bytestream2_get_bytes_left(gbc))
            return AVERROR_INVALIDDATA;

        /* Chunks are unpacked sequentially, ctx->tex_size is the uncompressed
         * size thus far */
        chunk->uncompressed_offset = ctx->tex_size;

        /* Fill out uncompressed size */
        if (chunk->compressor == HAP_COMP_SNAPPY) {
            GetByteContext gbc_tmp;
            int64_t uncompressed_size;
            bytestream2_init(&gbc_tmp, gbc->buffer + chunk->compressed_offset,
                             chunk->compressed_size);
            uncompressed_size = ff_snappy_peek_uncompressed_length(&gbc_tmp);
            if (uncompressed_size < 0) {
                return uncompressed_size;
            }
            chunk->uncompressed_size = uncompressed_size;
        } else if (chunk->compressor == HAP_COMP_NONE) {
            chunk->uncompressed_size = chunk->compressed_size;
        } else {
            return AVERROR_INVALIDDATA;
        }
        ctx->tex_size += chunk->uncompressed_size;
    }

    av_log(avctx, AV_LOG_DEBUG, "%s compressor\n", compressorstr);

    return ret;
}