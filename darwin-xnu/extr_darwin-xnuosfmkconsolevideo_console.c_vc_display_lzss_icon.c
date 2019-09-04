#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
typedef  int uint32_t ;
struct TYPE_4__ {int member_2; int member_3; int member_4; int* member_5; int const* member_6; int /*<<< orphan*/  member_1; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_1__ lzss_image_state ;
struct TYPE_5__ {int v_rowbytes; scalar_t__ v_baseaddr; } ;

/* Variables and functions */
 int F ; 
 int N ; 
 int THRESHOLD ; 
 int /*<<< orphan*/  vc_clean_boot_graphics () ; 
 int vc_decompress_lzss_next_pixel (int,TYPE_1__*) ; 
 TYPE_2__ vinfo ; 

int
vc_display_lzss_icon(uint32_t dst_x,       uint32_t dst_y,
                     uint32_t image_width, uint32_t image_height,
                     const uint8_t *compressed_image,
                     uint32_t       compressed_size, 
                     const uint8_t *clut)
{
    uint32_t* image_start;
    uint32_t bytes_per_pixel = 4;
    uint32_t bytes_per_row = vinfo.v_rowbytes;

    vc_clean_boot_graphics();

    image_start = (uint32_t *) (vinfo.v_baseaddr + (dst_y * bytes_per_row) + (dst_x * bytes_per_pixel));
    
    lzss_image_state state = {0, 0, image_width, image_height, bytes_per_row, image_start, clut};

    int rval = 0;

    const uint8_t *src = compressed_image;
    uint32_t srclen = compressed_size;

    /* ring buffer of size N, with extra F-1 bytes to aid string comparison */
    uint8_t text_buf[N + F - 1];
    const uint8_t *srcend = src + srclen;
    int  i, j, k, r, c;
    unsigned int flags;

    srcend = src + srclen;
    for (i = 0; i < N - F; i++)
        text_buf[i] = ' ';
    r = N - F;
    flags = 0;
    for ( ; ; ) {
        if (((flags >>= 1) & 0x100) == 0) {
            if (src < srcend) c = *src++; else break;
            flags = c | 0xFF00;  /* uses higher byte cleverly */
        }   /* to count eight */
        if (flags & 1) {
            if (src < srcend) c = *src++; else break;
            rval = vc_decompress_lzss_next_pixel(c, &state);
            if (rval != 0)
                return rval;
            text_buf[r++] = c;
            r &= (N - 1);
        } else {
            if (src < srcend) i = *src++; else break;
            if (src < srcend) j = *src++; else break;
            i |= ((j & 0xF0) << 4);
            j  =  (j & 0x0F) + THRESHOLD;
            for (k = 0; k <= j; k++) {
                c = text_buf[(i + k) & (N - 1)];
                rval = vc_decompress_lzss_next_pixel(c, &state);
                if (rval != 0 )
                    return rval;
                text_buf[r++] = c;
                r &= (N - 1);
            }
        }
    }
    return 0;
}