#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
struct TYPE_14__ {int /*<<< orphan*/ * priv_data; } ;
struct TYPE_13__ {int x_pos; int y_pos; int /*<<< orphan*/  region_id; } ;
struct TYPE_12__ {int* pbuf; int dirty; int width; int height; int depth; scalar_t__ has_computed_clut; } ;
typedef  TYPE_1__ DVBSubRegion ;
typedef  TYPE_2__ DVBSubObjectDisplay ;
typedef  int /*<<< orphan*/  DVBSubContext ;
typedef  TYPE_3__ AVCodecContext ;

/* Variables and functions */
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  AV_LOG_INFO ; 
 int /*<<< orphan*/  av_log (TYPE_3__*,int /*<<< orphan*/ ,char*,int const,...) ; 
 int dvbsub_read_2bit_string (TYPE_3__*,int*,int,int const**,int,int,int*,int) ; 
 int dvbsub_read_4bit_string (TYPE_3__*,int*,int,int const**,int,int,int*,int) ; 
 int dvbsub_read_8bit_string (TYPE_3__*,int*,int,int const**,int,int,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ff_dlog (TYPE_3__*,char*,...) ; 
 TYPE_1__* get_region (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void dvbsub_parse_pixel_data_block(AVCodecContext *avctx, DVBSubObjectDisplay *display,
                                          const uint8_t *buf, int buf_size, int top_bottom, int non_mod)
{
    DVBSubContext *ctx = avctx->priv_data;

    DVBSubRegion *region = get_region(ctx, display->region_id);
    const uint8_t *buf_end = buf + buf_size;
    uint8_t *pbuf;
    int x_pos, y_pos;
    int i;

    uint8_t map2to4[] = { 0x0,  0x7,  0x8,  0xf};
    uint8_t map2to8[] = {0x00, 0x77, 0x88, 0xff};
    uint8_t map4to8[] = {0x00, 0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77,
                         0x88, 0x99, 0xaa, 0xbb, 0xcc, 0xdd, 0xee, 0xff};
    uint8_t *map_table;

#if 0
    ff_dlog(avctx, "DVB pixel block size %d, %s field:\n", buf_size,
            top_bottom ? "bottom" : "top");

    for (i = 0; i < buf_size; i++) {
        if (i % 16 == 0)
            ff_dlog(avctx, "0x%8p: ", buf+i);

        ff_dlog(avctx, "%02x ", buf[i]);
        if (i % 16 == 15)
            ff_dlog(avctx, "\n");
    }

    if (i % 16)
        ff_dlog(avctx, "\n");
#endif

    if (!region)
        return;

    pbuf = region->pbuf;
    region->dirty = 1;

    x_pos = display->x_pos;
    y_pos = display->y_pos;

    y_pos += top_bottom;

    while (buf < buf_end) {
        if ((*buf!=0xf0 && x_pos >= region->width) || y_pos >= region->height) {
            av_log(avctx, AV_LOG_ERROR, "Invalid object location! %d-%d %d-%d %02x\n", x_pos, region->width, y_pos, region->height, *buf);
            return;
        }

        switch (*buf++) {
        case 0x10:
            if (region->depth == 8)
                map_table = map2to8;
            else if (region->depth == 4)
                map_table = map2to4;
            else
                map_table = NULL;

            x_pos = dvbsub_read_2bit_string(avctx, pbuf + (y_pos * region->width),
                                            region->width, &buf, buf_end - buf,
                                            non_mod, map_table, x_pos);
            break;
        case 0x11:
            if (region->depth < 4) {
                av_log(avctx, AV_LOG_ERROR, "4-bit pixel string in %d-bit region!\n", region->depth);
                return;
            }

            if (region->depth == 8)
                map_table = map4to8;
            else
                map_table = NULL;

            x_pos = dvbsub_read_4bit_string(avctx, pbuf + (y_pos * region->width),
                                            region->width, &buf, buf_end - buf,
                                            non_mod, map_table, x_pos);
            break;
        case 0x12:
            if (region->depth < 8) {
                av_log(avctx, AV_LOG_ERROR, "8-bit pixel string in %d-bit region!\n", region->depth);
                return;
            }

            x_pos = dvbsub_read_8bit_string(avctx, pbuf + (y_pos * region->width),
                                            region->width, &buf, buf_end - buf,
                                            non_mod, NULL, x_pos);
            break;

        case 0x20:
            map2to4[0] = (*buf) >> 4;
            map2to4[1] = (*buf++) & 0xf;
            map2to4[2] = (*buf) >> 4;
            map2to4[3] = (*buf++) & 0xf;
            break;
        case 0x21:
            for (i = 0; i < 4; i++)
                map2to8[i] = *buf++;
            break;
        case 0x22:
            for (i = 0; i < 16; i++)
                map4to8[i] = *buf++;
            break;

        case 0xf0:
            x_pos = display->x_pos;
            y_pos += 2;
            break;
        default:
            av_log(avctx, AV_LOG_INFO, "Unknown/unsupported pixel block 0x%x\n", *(buf-1));
        }
    }

    region->has_computed_clut = 0;
}