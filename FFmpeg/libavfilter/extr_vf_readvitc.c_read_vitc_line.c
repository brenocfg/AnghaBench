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
typedef  scalar_t__ uint8_t ;
struct TYPE_3__ {scalar_t__ scan_max; int* line_data; scalar_t__ threshold_white; scalar_t__ threshold_black; int grp_width; scalar_t__ threshold_gray; } ;
typedef  TYPE_1__ ReadVitcContext ;

/* Variables and functions */
 int FFMAX (int,int) ; 
 int FFMIN (int,scalar_t__) ; 
 int /*<<< orphan*/  LINE_DATA_SIZE ; 
 scalar_t__ get_pit_avg3 (scalar_t__*,int) ; 
 int get_vitc_crc (int*) ; 
 int /*<<< orphan*/  memset (int*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int read_vitc_line( ReadVitcContext *ctx, uint8_t *src, int line_size, int width, int height )
{
    uint8_t *scan_line;
    int grp_index, pit_index;
    int grp_start_pos;
    uint8_t pit_value;
    int x, y, res = 0;

    if (ctx->scan_max >= 0)
        height = FFMIN(height, ctx->scan_max);

    // scan lines for VITC data, starting from the top
    for (y = 0; y < height; y++) {
        scan_line = src;
        memset(ctx->line_data, 0, LINE_DATA_SIZE);
        grp_index = 0;
        x = 0;
        while ((x < width) && (grp_index < 9)) {
            // search next sync pattern
            while ((x < width) && (scan_line[x] < ctx->threshold_white))
                x++;
            while ((x < width) && (scan_line[x] > ctx->threshold_black))
                x++;
            x = FFMAX(x - ((ctx->grp_width+10) / 20), 1);  // step back a half pit
            grp_start_pos = x;
            if ((grp_start_pos + ctx->grp_width) > width)
                break;  // not enough pixels for reading a whole pit group
            pit_value = get_pit_avg3(scan_line, x);
            if (pit_value < ctx->threshold_white)
               break;  // first sync bit mismatch
            x = grp_start_pos + ((ctx->grp_width) / 10);
            pit_value = get_pit_avg3(scan_line, x);
            if (pit_value > ctx->threshold_black )
                break;  // second sync bit mismatch
            for (pit_index = 0; pit_index <= 7; pit_index++) {
                x = grp_start_pos + (((pit_index+2)*ctx->grp_width) / 10);
                pit_value = get_pit_avg3(scan_line, x);
                if (pit_value > ctx->threshold_gray)
                    ctx->line_data[grp_index] |= (1 << pit_index);
            }
            grp_index++;
        }
        if ((grp_index == 9) && (get_vitc_crc(ctx->line_data) == ctx->line_data[8])) {
            res = 1;
            break;
        }
        src += line_size;
    }

    return res;
}