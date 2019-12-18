#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ pix_fmt; } ;
typedef  TYPE_1__ CinepakEncContext ;

/* Variables and functions */
 scalar_t__ AV_PIX_FMT_RGB24 ; 
 int /*<<< orphan*/  AV_WB32 (unsigned char*,int) ; 
 int write_chunk_header (unsigned char*,int,int) ; 

__attribute__((used)) static int encode_codebook(CinepakEncContext *s, int *codebook, int size,
                           int chunk_type_yuv, int chunk_type_gray,
                           unsigned char *buf)
{
    int x, y, ret, entry_size = s->pix_fmt == AV_PIX_FMT_RGB24 ? 6 : 4;
    int incremental_codebook_replacement_mode = 0; // hardcoded here,
    // the compiler should notice that this is a constant -- rl

    ret = write_chunk_header(buf,
                             s->pix_fmt == AV_PIX_FMT_RGB24 ?
                             chunk_type_yuv  + (incremental_codebook_replacement_mode ? 1 : 0) :
                             chunk_type_gray + (incremental_codebook_replacement_mode ? 1 : 0),
                             entry_size * size +
                             (incremental_codebook_replacement_mode ? (size + 31) / 32 * 4 : 0));

    // we do codebook encoding according to the "intra" mode
    // but we keep the "dead" code for reference in case we will want
    // to use incremental codebook updates (which actually would give us
    // "kind of" motion compensation, especially in 1 strip/frame case) -- rl
    // (of course, the code will be not useful as-is)
    if (incremental_codebook_replacement_mode) {
        int flags = 0;
        int flagsind;
        for (x = 0; x < size; x++) {
            if (flags == 0) {
                flagsind = ret;
                ret     += 4;
                flags    = 0x80000000;
            } else
                flags = ((flags >> 1) | 0x80000000);
            for (y = 0; y < entry_size; y++)
                buf[ret++] = codebook[y + x * entry_size] ^ (y >= 4 ? 0x80 : 0);
            if ((flags & 0xffffffff) == 0xffffffff) {
                AV_WB32(&buf[flagsind], flags);
                flags = 0;
            }
        }
        if (flags)
            AV_WB32(&buf[flagsind], flags);
    } else
        for (x = 0; x < size; x++)
            for (y = 0; y < entry_size; y++)
                buf[ret++] = codebook[y + x * entry_size] ^ (y >= 4 ? 0x80 : 0);

    return ret;
}