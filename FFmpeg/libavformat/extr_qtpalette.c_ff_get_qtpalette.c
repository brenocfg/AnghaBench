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
typedef  int uint8_t ;
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  AVIOContext ;

/* Variables and functions */
 int AV_CODEC_ID_CINEPAK ; 
 int /*<<< orphan*/  SEEK_CUR ; 
 int avio_r8 (int /*<<< orphan*/ *) ; 
 int avio_rb16 (int /*<<< orphan*/ *) ; 
 int avio_rb32 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  avio_seek (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  avio_skip (int /*<<< orphan*/ *,int) ; 
 int* ff_qt_default_palette_16 ; 
 int* ff_qt_default_palette_2 ; 
 int* ff_qt_default_palette_256 ; 
 int* ff_qt_default_palette_4 ; 

int ff_get_qtpalette(int codec_id, AVIOContext *pb, uint32_t *palette)
{
    int tmp, bit_depth, color_table_id, greyscale, i;

    avio_seek(pb, 82, SEEK_CUR);

    /* Get the bit depth and greyscale state */
    tmp = avio_rb16(pb);
    bit_depth = tmp & 0x1F;
    greyscale = tmp & 0x20;

    /* Get the color table ID */
    color_table_id = avio_rb16(pb);

    /* Do not create a greyscale palette for Cinepak */
    if (greyscale && codec_id == AV_CODEC_ID_CINEPAK)
        return 0;

    /* If the depth is 1, 2, 4, or 8 bpp, file is palettized. */
    if ((bit_depth == 1 || bit_depth == 2 || bit_depth == 4 || bit_depth == 8)) {
        uint32_t color_count, color_start, color_end;
        uint32_t r, g, b;

        /* Ignore the greyscale bit for 1-bit video and sample
         * descriptions containing a color table. */
        if (greyscale && bit_depth > 1 && color_table_id) {
            int color_index, color_dec;
            /* compute the greyscale palette */
            color_count = 1 << bit_depth;
            color_index = 255;
            color_dec   = 256 / (color_count - 1);
            for (i = 0; i < color_count; i++) {
                r = g = b = color_index;
                palette[i] = (0xFFU << 24) | (r << 16) | (g << 8) | (b);
                color_index -= color_dec;
                if (color_index < 0)
                    color_index = 0;
            }
        } else if (color_table_id) {
            /* The color table ID is non-zero. Interpret this as
             * being -1, which means use the default Macintosh
             * color table */
            const uint8_t *color_table;
            color_count = 1 << bit_depth;
            if (bit_depth == 1)
                color_table = ff_qt_default_palette_2;
            else if (bit_depth == 2)
                color_table = ff_qt_default_palette_4;
            else if (bit_depth == 4)
                color_table = ff_qt_default_palette_16;
            else
                color_table = ff_qt_default_palette_256;
            for (i = 0; i < color_count; i++) {
                r = color_table[i * 3 + 0];
                g = color_table[i * 3 + 1];
                b = color_table[i * 3 + 2];
                palette[i] = (0xFFU << 24) | (r << 16) | (g << 8) | (b);
            }
        } else {
            /* The color table ID is 0; the color table is in the sample
             * description */
            color_start = avio_rb32(pb);
            avio_rb16(pb); /* color table flags */
            color_end = avio_rb16(pb);
            if ((color_start <= 255) && (color_end <= 255)) {
                for (i = color_start; i <= color_end; i++) {
                    /* Each color is made of four unsigned 16 bit integers. The
                     * first integer is 0, the remaining integers are the red,
                     * the green and the blue values. We only use the top 8 bit. */
                    avio_skip(pb, 2);
                    r = avio_r8(pb);
                    avio_r8(pb);
                    g = avio_r8(pb);
                    avio_r8(pb);
                    b = avio_r8(pb);
                    avio_r8(pb);
                    palette[i] = (0xFFU << 24) | (r << 16) | (g << 8) | (b);
                }
            }
        }

        return 1;
    }

    return 0;
}