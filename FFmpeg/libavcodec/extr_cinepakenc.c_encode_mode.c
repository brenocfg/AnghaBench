#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  unsigned int uint32_t ;
struct TYPE_13__ {int mode; scalar_t__ v1_size; int /*<<< orphan*/  v1_codebook; scalar_t__ v4_size; int /*<<< orphan*/  v4_codebook; } ;
typedef  TYPE_1__ strip_info ;
struct TYPE_14__ {scalar_t__ best_encoding; unsigned char v1_vector; unsigned char* v4_vector; } ;
typedef  TYPE_2__ mb_info ;
struct TYPE_15__ {int w; TYPE_2__* mb; int /*<<< orphan*/  skip_empty_cb; } ;
typedef  TYPE_3__ CinepakEncContext ;

/* Variables and functions */
 int /*<<< orphan*/  AV_WB32 (unsigned char*,unsigned int) ; 
 int CHUNK_HEADER_SIZE ; 
 scalar_t__ ENC_SKIP ; 
 scalar_t__ ENC_V1 ; 
 scalar_t__ ENC_V4 ; 
 int FFMIN (int,int) ; 
 int MB_AREA ; 
 scalar_t__ MB_SIZE ; 
#define  MODE_MC 130 
#define  MODE_V1_ONLY 129 
#define  MODE_V1_V4 128 
 int /*<<< orphan*/  copy_mb (TYPE_3__*,int /*<<< orphan*/ **,int*,int /*<<< orphan*/ **,int*) ; 
 int /*<<< orphan*/  decode_v1_vector (TYPE_3__*,int /*<<< orphan*/ **,int*,unsigned char,TYPE_1__*) ; 
 int /*<<< orphan*/  decode_v4_vector (TYPE_3__*,int /*<<< orphan*/ **,int*,unsigned char*,TYPE_1__*) ; 
 scalar_t__ encode_codebook (TYPE_3__*,int /*<<< orphan*/ ,scalar_t__,int,int,unsigned char*) ; 
 int /*<<< orphan*/  get_sub_picture (TYPE_3__*,int,int,int /*<<< orphan*/ **,int*,int /*<<< orphan*/ **,int*) ; 
 int /*<<< orphan*/  memcpy (unsigned char*,unsigned char*,int) ; 
 int write_chunk_header (unsigned char*,int,int) ; 

__attribute__((used)) static int encode_mode(CinepakEncContext *s, int h,
                       uint8_t *scratch_data[4], int scratch_linesize[4],
                       uint8_t *last_data[4], int last_linesize[4],
                       strip_info *info, unsigned char *buf)
{
    int x, y, z, bits, temp_size, header_ofs, ret = 0, mb_count = s->w * h / MB_AREA;
    int needs_extra_bit, should_write_temp;
    uint32_t flags;
    unsigned char temp[64]; // 32/2 = 16 V4 blocks at 4 B each -> 64 B
    mb_info *mb;
    uint8_t *sub_scratch_data[4] = { 0 }, *sub_last_data[4] = { 0 };
    int sub_scratch_linesize[4] = { 0 }, sub_last_linesize[4] = { 0 };

    // encode codebooks
    ////// MacOS vintage decoder compatibility dictates the presence of
    ////// the codebook chunk even when the codebook is empty - pretty dumb...
    ////// and also the certain order of the codebook chunks -- rl
    if (info->v4_size || !s->skip_empty_cb)
        ret += encode_codebook(s, info->v4_codebook, info->v4_size, 0x20, 0x24, buf + ret);

    if (info->v1_size || !s->skip_empty_cb)
        ret += encode_codebook(s, info->v1_codebook, info->v1_size, 0x22, 0x26, buf + ret);

    // update scratch picture
    for (z = y = 0; y < h; y += MB_SIZE)
        for (x = 0; x < s->w; x += MB_SIZE, z++) {
            mb = &s->mb[z];

            get_sub_picture(s, x, y, scratch_data, scratch_linesize,
                            sub_scratch_data, sub_scratch_linesize);

            if (info->mode == MODE_MC && mb->best_encoding == ENC_SKIP) {
                get_sub_picture(s, x, y, last_data, last_linesize,
                                sub_last_data, sub_last_linesize);
                copy_mb(s, sub_scratch_data, sub_scratch_linesize,
                        sub_last_data, sub_last_linesize);
            } else if (info->mode == MODE_V1_ONLY || mb->best_encoding == ENC_V1)
                decode_v1_vector(s, sub_scratch_data, sub_scratch_linesize,
                                 mb->v1_vector, info);
            else
                decode_v4_vector(s, sub_scratch_data, sub_scratch_linesize,
                                 mb->v4_vector, info);
        }

    switch (info->mode) {
    case MODE_V1_ONLY:
        ret += write_chunk_header(buf + ret, 0x32, mb_count);

        for (x = 0; x < mb_count; x++)
            buf[ret++] = s->mb[x].v1_vector;

        break;
    case MODE_V1_V4:
        // remember header position
        header_ofs = ret;
        ret       += CHUNK_HEADER_SIZE;

        for (x = 0; x < mb_count; x += 32) {
            flags = 0;
            for (y = x; y < FFMIN(x + 32, mb_count); y++)
                if (s->mb[y].best_encoding == ENC_V4)
                    flags |= 1U << (31 - y + x);

            AV_WB32(&buf[ret], flags);
            ret += 4;

            for (y = x; y < FFMIN(x + 32, mb_count); y++) {
                mb = &s->mb[y];

                if (mb->best_encoding == ENC_V1)
                    buf[ret++] = mb->v1_vector;
                else
                    for (z = 0; z < 4; z++)
                        buf[ret++] = mb->v4_vector[z];
            }
        }

        write_chunk_header(buf + header_ofs, 0x30, ret - header_ofs - CHUNK_HEADER_SIZE);

        break;
    case MODE_MC:
        // remember header position
        header_ofs = ret;
        ret       += CHUNK_HEADER_SIZE;
        flags      = bits = temp_size = 0;

        for (x = 0; x < mb_count; x++) {
            mb                = &s->mb[x];
            flags            |= (uint32_t)(mb->best_encoding != ENC_SKIP) << (31 - bits++);
            needs_extra_bit   = 0;
            should_write_temp = 0;

            if (mb->best_encoding != ENC_SKIP) {
                if (bits < 32)
                    flags |= (uint32_t)(mb->best_encoding == ENC_V4) << (31 - bits++);
                else
                    needs_extra_bit = 1;
            }

            if (bits == 32) {
                AV_WB32(&buf[ret], flags);
                ret  += 4;
                flags = bits = 0;

                if (mb->best_encoding == ENC_SKIP || needs_extra_bit) {
                    memcpy(&buf[ret], temp, temp_size);
                    ret      += temp_size;
                    temp_size = 0;
                } else
                    should_write_temp = 1;
            }

            if (needs_extra_bit) {
                flags = (uint32_t)(mb->best_encoding == ENC_V4) << 31;
                bits  = 1;
            }

            if (mb->best_encoding == ENC_V1)
                temp[temp_size++] = mb->v1_vector;
            else if (mb->best_encoding == ENC_V4)
                for (z = 0; z < 4; z++)
                    temp[temp_size++] = mb->v4_vector[z];

            if (should_write_temp) {
                memcpy(&buf[ret], temp, temp_size);
                ret      += temp_size;
                temp_size = 0;
            }
        }

        if (bits > 0) {
            AV_WB32(&buf[ret], flags);
            ret += 4;
            memcpy(&buf[ret], temp, temp_size);
            ret += temp_size;
        }

        write_chunk_header(buf + header_ofs, 0x31, ret - header_ofs - CHUNK_HEADER_SIZE);

        break;
    }

    return ret;
}