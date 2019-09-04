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
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_6__ {int chunk_count; int opt_tex_fmt; TYPE_1__* chunks; } ;
struct TYPE_5__ {int compressor; int /*<<< orphan*/  compressed_size; } ;
typedef  int /*<<< orphan*/  PutByteContext ;
typedef  TYPE_2__ HapContext ;

/* Variables and functions */
 int HAP_COMP_COMPLEX ; 
 int /*<<< orphan*/  HAP_HDR_LONG ; 
 int /*<<< orphan*/  HAP_HDR_SHORT ; 
 int HAP_ST_COMPRESSOR_TABLE ; 
 int HAP_ST_DECODE_INSTRUCTIONS ; 
 int HAP_ST_SIZE_TABLE ; 
 int /*<<< orphan*/  bytestream2_init_writer (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  bytestream2_put_byte (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  bytestream2_put_le32 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int hap_decode_instructions_length (TYPE_2__*) ; 
 int /*<<< orphan*/  hap_write_section_header (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static void hap_write_frame_header(HapContext *ctx, uint8_t *dst, int frame_length)
{
    PutByteContext pbc;
    int i;

    bytestream2_init_writer(&pbc, dst, frame_length);
    if (ctx->chunk_count == 1) {
        /* Write a simple header */
        hap_write_section_header(&pbc, HAP_HDR_LONG, frame_length - 8,
                                 ctx->chunks[0].compressor | ctx->opt_tex_fmt);
    } else {
        /* Write a complex header with Decode Instructions Container */
        hap_write_section_header(&pbc, HAP_HDR_LONG, frame_length - 8,
                                 HAP_COMP_COMPLEX | ctx->opt_tex_fmt);
        hap_write_section_header(&pbc, HAP_HDR_SHORT, hap_decode_instructions_length(ctx),
                                 HAP_ST_DECODE_INSTRUCTIONS);
        hap_write_section_header(&pbc, HAP_HDR_SHORT, ctx->chunk_count,
                                 HAP_ST_COMPRESSOR_TABLE);

        for (i = 0; i < ctx->chunk_count; i++) {
            bytestream2_put_byte(&pbc, ctx->chunks[i].compressor >> 4);
        }

        hap_write_section_header(&pbc, HAP_HDR_SHORT, ctx->chunk_count * 4,
                                 HAP_ST_SIZE_TABLE);

        for (i = 0; i < ctx->chunk_count; i++) {
            bytestream2_put_le32(&pbc, ctx->chunks[i].compressed_size);
        }
    }
}