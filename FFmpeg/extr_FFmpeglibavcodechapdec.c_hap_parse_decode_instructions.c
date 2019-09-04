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
typedef  enum HapSectionType { ____Placeholder_HapSectionType } HapSectionType ;
struct TYPE_6__ {int chunk_count; TYPE_1__* chunks; int /*<<< orphan*/  gbc; } ;
struct TYPE_5__ {int compressor; size_t compressed_offset; void* compressed_size; } ;
typedef  TYPE_2__ HapContext ;
typedef  int /*<<< orphan*/  GetByteContext ;

/* Variables and functions */
 int AVERROR_INVALIDDATA ; 
#define  HAP_ST_COMPRESSOR_TABLE 130 
#define  HAP_ST_OFFSET_TABLE 129 
#define  HAP_ST_SIZE_TABLE 128 
 int bytestream2_get_byte (int /*<<< orphan*/ *) ; 
 int bytestream2_get_bytes_left (int /*<<< orphan*/ *) ; 
 void* bytestream2_get_le32 (int /*<<< orphan*/ *) ; 
 int ff_hap_parse_section_header (int /*<<< orphan*/ *,int*,int*) ; 
 int ff_hap_set_chunk_count (TYPE_2__*,int,int) ; 

__attribute__((used)) static int hap_parse_decode_instructions(HapContext *ctx, int size)
{
    GetByteContext *gbc = &ctx->gbc;
    int section_size;
    enum HapSectionType section_type;
    int is_first_table = 1, had_offsets = 0, had_compressors = 0, had_sizes = 0;
    int i, ret;

    while (size > 0) {
        int stream_remaining = bytestream2_get_bytes_left(gbc);
        ret = ff_hap_parse_section_header(gbc, &section_size, &section_type);
        if (ret != 0)
            return ret;

        size -= stream_remaining - bytestream2_get_bytes_left(gbc);

        switch (section_type) {
            case HAP_ST_COMPRESSOR_TABLE:
                ret = ff_hap_set_chunk_count(ctx, section_size, is_first_table);
                if (ret != 0)
                    return ret;
                for (i = 0; i < section_size; i++) {
                    ctx->chunks[i].compressor = bytestream2_get_byte(gbc) << 4;
                }
                had_compressors = 1;
                is_first_table = 0;
                break;
            case HAP_ST_SIZE_TABLE:
                ret = ff_hap_set_chunk_count(ctx, section_size / 4, is_first_table);
                if (ret != 0)
                    return ret;
                for (i = 0; i < section_size / 4; i++) {
                    ctx->chunks[i].compressed_size = bytestream2_get_le32(gbc);
                }
                had_sizes = 1;
                is_first_table = 0;
                break;
            case HAP_ST_OFFSET_TABLE:
                ret = ff_hap_set_chunk_count(ctx, section_size / 4, is_first_table);
                if (ret != 0)
                    return ret;
                for (i = 0; i < section_size / 4; i++) {
                    ctx->chunks[i].compressed_offset = bytestream2_get_le32(gbc);
                }
                had_offsets = 1;
                is_first_table = 0;
                break;
            default:
                break;
        }
        size -= section_size;
    }

    if (!had_sizes || !had_compressors)
        return AVERROR_INVALIDDATA;

    /* The offsets table is optional. If not present than calculate offsets by
     * summing the sizes of preceding chunks. */
    if (!had_offsets) {
        size_t running_size = 0;
        for (i = 0; i < ctx->chunk_count; i++) {
            ctx->chunks[i].compressed_offset = running_size;
            running_size += ctx->chunks[i].compressed_size;
        }
    }

    return 0;
}