#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_7__ {int frame_size; int /*<<< orphan*/  avctx; int /*<<< orphan*/  gb; } ;
typedef  TYPE_1__ DCAXllDecoder ;
typedef  int /*<<< orphan*/  DCAExssAsset ;

/* Variables and functions */
 int AVERROR_INVALIDDATA ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  av_log (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ ff_dca_seek_bits (int /*<<< orphan*/ *,int) ; 
 int init_get_bits8 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int parse_band_data (TYPE_1__*) ; 
 int parse_common_header (TYPE_1__*) ; 
 int parse_navi_table (TYPE_1__*) ; 
 int parse_sub_headers (TYPE_1__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int parse_frame(DCAXllDecoder *s, uint8_t *data, int size, DCAExssAsset *asset)
{
    int ret;

    if ((ret = init_get_bits8(&s->gb, data, size)) < 0)
        return ret;
    if ((ret = parse_common_header(s)) < 0)
        return ret;
    if ((ret = parse_sub_headers(s, asset)) < 0)
        return ret;
    if ((ret = parse_navi_table(s)) < 0)
        return ret;
    if ((ret = parse_band_data(s)) < 0)
        return ret;
    if (ff_dca_seek_bits(&s->gb, s->frame_size * 8)) {
        av_log(s->avctx, AV_LOG_ERROR, "Read past end of XLL frame\n");
        return AVERROR_INVALIDDATA;
    }
    return ret;
}