#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  enum AVPacketSideDataType { ____Placeholder_AVPacketSideDataType } AVPacketSideDataType ;
struct TYPE_8__ {int side_data_elems; TYPE_1__* side_data; int /*<<< orphan*/  stream_index; int /*<<< orphan*/  flags; int /*<<< orphan*/  duration; int /*<<< orphan*/  pos; int /*<<< orphan*/  dts; int /*<<< orphan*/  pts; } ;
struct TYPE_7__ {int type; int size; int /*<<< orphan*/ * data; } ;
typedef  TYPE_2__ AVPacket ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  av_packet_free_side_data (TYPE_2__*) ; 
 int /*<<< orphan*/ * av_packet_new_side_data (TYPE_2__*,int,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

int av_packet_copy_props(AVPacket *dst, const AVPacket *src)
{
    int i;

    dst->pts                  = src->pts;
    dst->dts                  = src->dts;
    dst->pos                  = src->pos;
    dst->duration             = src->duration;
#if FF_API_CONVERGENCE_DURATION
FF_DISABLE_DEPRECATION_WARNINGS
    dst->convergence_duration = src->convergence_duration;
FF_ENABLE_DEPRECATION_WARNINGS
#endif
    dst->flags                = src->flags;
    dst->stream_index         = src->stream_index;

    dst->side_data            = NULL;
    dst->side_data_elems      = 0;
    for (i = 0; i < src->side_data_elems; i++) {
        enum AVPacketSideDataType type = src->side_data[i].type;
        int size          = src->side_data[i].size;
        uint8_t *src_data = src->side_data[i].data;
        uint8_t *dst_data = av_packet_new_side_data(dst, type, size);

        if (!dst_data) {
            av_packet_free_side_data(dst);
            return AVERROR(ENOMEM);
        }
        memcpy(dst_data, src_data, size);
    }

    return 0;
}