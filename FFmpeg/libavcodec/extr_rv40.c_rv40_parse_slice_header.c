#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int width; int height; int /*<<< orphan*/  avctx; } ;
struct TYPE_9__ {TYPE_1__ s; } ;
struct TYPE_8__ {int type; int width; int height; void* start; void* pts; void* vlc_set; void* quant; } ;
typedef  TYPE_2__ SliceInfo ;
typedef  TYPE_3__ RV34DecContext ;
typedef  int /*<<< orphan*/  GetBitContext ;

/* Variables and functions */
 int AVERROR_INVALIDDATA ; 
 int av_image_check_size (int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ff_rv34_get_start_offset (int /*<<< orphan*/ *,int) ; 
 void* get_bits (int /*<<< orphan*/ *,int) ; 
 scalar_t__ get_bits1 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rv40_parse_picture_size (int /*<<< orphan*/ *,int*,int*) ; 
 int /*<<< orphan*/  skip_bits1 (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int rv40_parse_slice_header(RV34DecContext *r, GetBitContext *gb, SliceInfo *si)
{
    int mb_bits;
    int w = r->s.width, h = r->s.height;
    int mb_size;
    int ret;

    memset(si, 0, sizeof(SliceInfo));
    if(get_bits1(gb))
        return AVERROR_INVALIDDATA;
    si->type = get_bits(gb, 2);
    if(si->type == 1) si->type = 0;
    si->quant = get_bits(gb, 5);
    if(get_bits(gb, 2))
        return AVERROR_INVALIDDATA;
    si->vlc_set = get_bits(gb, 2);
    skip_bits1(gb);
    si->pts = get_bits(gb, 13);
    if(!si->type || !get_bits1(gb))
        rv40_parse_picture_size(gb, &w, &h);
    if ((ret = av_image_check_size(w, h, 0, r->s.avctx)) < 0)
        return ret;
    si->width  = w;
    si->height = h;
    mb_size = ((w + 15) >> 4) * ((h + 15) >> 4);
    mb_bits = ff_rv34_get_start_offset(gb, mb_size);
    si->start = get_bits(gb, mb_bits);

    return 0;
}