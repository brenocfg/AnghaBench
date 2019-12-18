#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct TYPE_7__ {int mb_height; int mb_width; int mb_stride; int /*<<< orphan*/  gb; TYPE_1__* current_picture_ptr; } ;
struct TYPE_6__ {int /*<<< orphan*/  skip_type; TYPE_3__ s; } ;
typedef  TYPE_2__ Wmv2Context ;
struct TYPE_5__ {int* mb_type; } ;
typedef  TYPE_3__ MpegEncContext ;

/* Variables and functions */
 int AVERROR_INVALIDDATA ; 
 int /*<<< orphan*/  IS_SKIP (int) ; 
 int MB_TYPE_16x16 ; 
 int MB_TYPE_L0 ; 
 int MB_TYPE_SKIP ; 
#define  SKIP_TYPE_COL 131 
#define  SKIP_TYPE_MPEG 130 
#define  SKIP_TYPE_NONE 129 
#define  SKIP_TYPE_ROW 128 
 int /*<<< orphan*/  get_bits (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  get_bits1 (int /*<<< orphan*/ *) ; 
 int get_bits_left (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int parse_mb_skip(Wmv2Context *w)
{
    int mb_x, mb_y;
    int coded_mb_count = 0;
    MpegEncContext *const s = &w->s;
    uint32_t *const mb_type = s->current_picture_ptr->mb_type;

    w->skip_type = get_bits(&s->gb, 2);
    switch (w->skip_type) {
    case SKIP_TYPE_NONE:
        for (mb_y = 0; mb_y < s->mb_height; mb_y++)
            for (mb_x = 0; mb_x < s->mb_width; mb_x++)
                mb_type[mb_y * s->mb_stride + mb_x] =
                    MB_TYPE_16x16 | MB_TYPE_L0;
        break;
    case SKIP_TYPE_MPEG:
        if (get_bits_left(&s->gb) < s->mb_height * s->mb_width)
            return AVERROR_INVALIDDATA;
        for (mb_y = 0; mb_y < s->mb_height; mb_y++)
            for (mb_x = 0; mb_x < s->mb_width; mb_x++)
                mb_type[mb_y * s->mb_stride + mb_x] =
                    (get_bits1(&s->gb) ? MB_TYPE_SKIP : 0) | MB_TYPE_16x16 | MB_TYPE_L0;
        break;
    case SKIP_TYPE_ROW:
        for (mb_y = 0; mb_y < s->mb_height; mb_y++) {
            if (get_bits_left(&s->gb) < 1)
                return AVERROR_INVALIDDATA;
            if (get_bits1(&s->gb)) {
                for (mb_x = 0; mb_x < s->mb_width; mb_x++)
                    mb_type[mb_y * s->mb_stride + mb_x] =
                        MB_TYPE_SKIP | MB_TYPE_16x16 | MB_TYPE_L0;
            } else {
                for (mb_x = 0; mb_x < s->mb_width; mb_x++)
                    mb_type[mb_y * s->mb_stride + mb_x] =
                        (get_bits1(&s->gb) ? MB_TYPE_SKIP : 0) | MB_TYPE_16x16 | MB_TYPE_L0;
            }
        }
        break;
    case SKIP_TYPE_COL:
        for (mb_x = 0; mb_x < s->mb_width; mb_x++) {
            if (get_bits_left(&s->gb) < 1)
                return AVERROR_INVALIDDATA;
            if (get_bits1(&s->gb)) {
                for (mb_y = 0; mb_y < s->mb_height; mb_y++)
                    mb_type[mb_y * s->mb_stride + mb_x] =
                        MB_TYPE_SKIP | MB_TYPE_16x16 | MB_TYPE_L0;
            } else {
                for (mb_y = 0; mb_y < s->mb_height; mb_y++)
                    mb_type[mb_y * s->mb_stride + mb_x] =
                        (get_bits1(&s->gb) ? MB_TYPE_SKIP : 0) | MB_TYPE_16x16 | MB_TYPE_L0;
            }
        }
        break;
    }

    for (mb_y = 0; mb_y < s->mb_height; mb_y++)
        for (mb_x = 0; mb_x < s->mb_width; mb_x++)
            coded_mb_count += !IS_SKIP(mb_type[mb_y * s->mb_stride + mb_x]);

    if (coded_mb_count > get_bits_left(&s->gb))
        return AVERROR_INVALIDDATA;

    return 0;
}