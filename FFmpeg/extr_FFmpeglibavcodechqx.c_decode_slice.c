#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int width; int height; int /*<<< orphan*/  (* decode_func ) (TYPE_1__*,int,int,int) ;} ;
typedef  TYPE_1__ HQXContext ;

/* Variables and functions */
 int* shuffle_16 ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*,int,int,int) ; 

__attribute__((used)) static int decode_slice(HQXContext *ctx, int slice_no)
{
    int mb_w = (ctx->width  + 15) >> 4;
    int mb_h = (ctx->height + 15) >> 4;
    int grp_w = (mb_w + 4) / 5;
    int grp_h = (mb_h + 4) / 5;
    int grp_h_edge = grp_w * (mb_w / grp_w);
    int grp_v_edge = grp_h * (mb_h / grp_h);
    int grp_v_rest = mb_w - grp_h_edge;
    int grp_h_rest = mb_h - grp_v_edge;
    int num_mbs = mb_w * mb_h;
    int num_tiles = (num_mbs + 479) / 480;
    int std_tile_blocks = num_mbs / (16 * num_tiles);
    int g_tile = slice_no * num_tiles;
    int blk_addr, loc_addr, mb_x, mb_y, pos, loc_row, i;
    int tile_blocks, tile_limit, tile_no;

    for (tile_no = 0; tile_no < num_tiles; tile_no++, g_tile++) {
        tile_blocks = std_tile_blocks;
        tile_limit = -1;
        if (g_tile < num_mbs - std_tile_blocks * 16 * num_tiles) {
            tile_limit = num_mbs / (16 * num_tiles);
            tile_blocks++;
        }
        for (i = 0; i < tile_blocks; i++) {
            if (i == tile_limit)
                blk_addr = g_tile + 16 * num_tiles * i;
            else
                blk_addr = tile_no + 16 * num_tiles * i +
                           num_tiles * shuffle_16[(i + slice_no) & 0xF];
            loc_row  = grp_h * (blk_addr / (grp_h * mb_w));
            loc_addr =          blk_addr % (grp_h * mb_w);
            if (loc_row >= grp_v_edge) {
                mb_x = grp_w * (loc_addr / (grp_h_rest * grp_w));
                pos  =          loc_addr % (grp_h_rest * grp_w);
            } else {
                mb_x = grp_w * (loc_addr / (grp_h * grp_w));
                pos  =          loc_addr % (grp_h * grp_w);
            }
            if (mb_x >= grp_h_edge) {
                mb_x +=            pos % grp_v_rest;
                mb_y  = loc_row + (pos / grp_v_rest);
            } else {
                mb_x +=            pos % grp_w;
                mb_y  = loc_row + (pos / grp_w);
            }
            ctx->decode_func(ctx, slice_no, mb_x * 16, mb_y * 16);
        }
    }

    return 0;
}