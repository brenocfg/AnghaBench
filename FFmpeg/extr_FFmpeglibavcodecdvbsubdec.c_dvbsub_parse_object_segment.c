#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
struct TYPE_11__ {int /*<<< orphan*/ * priv_data; } ;
struct TYPE_10__ {TYPE_1__* display_list; } ;
struct TYPE_9__ {struct TYPE_9__* object_list_next; } ;
typedef  TYPE_1__ DVBSubObjectDisplay ;
typedef  TYPE_2__ DVBSubObject ;
typedef  int /*<<< orphan*/  DVBSubContext ;
typedef  TYPE_3__ AVCodecContext ;

/* Variables and functions */
 int AVERROR_INVALIDDATA ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int AV_RB16 (int const*) ; 
 int /*<<< orphan*/  av_log (TYPE_3__*,int /*<<< orphan*/ ,char*,int,...) ; 
 int /*<<< orphan*/  dvbsub_parse_pixel_data_block (TYPE_3__*,TYPE_1__*,int const*,int,int,int) ; 
 TYPE_2__* get_object (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int dvbsub_parse_object_segment(AVCodecContext *avctx,
                                       const uint8_t *buf, int buf_size)
{
    DVBSubContext *ctx = avctx->priv_data;

    const uint8_t *buf_end = buf + buf_size;
    int object_id;
    DVBSubObject *object;
    DVBSubObjectDisplay *display;
    int top_field_len, bottom_field_len;

    int coding_method, non_modifying_color;

    object_id = AV_RB16(buf);
    buf += 2;

    object = get_object(ctx, object_id);

    if (!object)
        return AVERROR_INVALIDDATA;

    coding_method = ((*buf) >> 2) & 3;
    non_modifying_color = ((*buf++) >> 1) & 1;

    if (coding_method == 0) {
        top_field_len = AV_RB16(buf);
        buf += 2;
        bottom_field_len = AV_RB16(buf);
        buf += 2;

        if (buf + top_field_len + bottom_field_len > buf_end) {
            av_log(avctx, AV_LOG_ERROR, "Field data size %d+%d too large\n", top_field_len, bottom_field_len);
            return AVERROR_INVALIDDATA;
        }

        for (display = object->display_list; display; display = display->object_list_next) {
            const uint8_t *block = buf;
            int bfl = bottom_field_len;

            dvbsub_parse_pixel_data_block(avctx, display, block, top_field_len, 0,
                                            non_modifying_color);

            if (bottom_field_len > 0)
                block = buf + top_field_len;
            else
                bfl = top_field_len;

            dvbsub_parse_pixel_data_block(avctx, display, block, bfl, 1,
                                            non_modifying_color);
        }

/*  } else if (coding_method == 1) {*/

    } else {
        av_log(avctx, AV_LOG_ERROR, "Unknown object coding %d\n", coding_method);
    }

    return 0;
}