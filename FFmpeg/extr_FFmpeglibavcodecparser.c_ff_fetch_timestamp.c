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
struct TYPE_3__ {scalar_t__ dts; scalar_t__ pts; int pos; scalar_t__ offset; scalar_t__ cur_offset; scalar_t__* cur_frame_offset; scalar_t__ frame_offset; scalar_t__ next_frame_offset; scalar_t__* cur_frame_end; scalar_t__* cur_frame_dts; scalar_t__* cur_frame_pts; int* cur_frame_pos; } ;
typedef  TYPE_1__ AVCodecParserContext ;

/* Variables and functions */
 scalar_t__ AV_NOPTS_VALUE ; 
 int AV_PARSER_PTS_NB ; 
 scalar_t__ INT64_MAX ; 

void ff_fetch_timestamp(AVCodecParserContext *s, int off, int remove, int fuzzy)
{
    int i;

    if (!fuzzy) {
        s->dts    =
        s->pts    = AV_NOPTS_VALUE;
        s->pos    = -1;
        s->offset = 0;
    }
    for (i = 0; i < AV_PARSER_PTS_NB; i++) {
        if (s->cur_offset + off >= s->cur_frame_offset[i] &&
            (s->frame_offset < s->cur_frame_offset[i] ||
             (!s->frame_offset && !s->next_frame_offset)) && // first field/frame
            // check disabled since MPEG-TS does not send complete PES packets
            /*s->next_frame_offset + off <*/  s->cur_frame_end[i]){

            if (!fuzzy || s->cur_frame_dts[i] != AV_NOPTS_VALUE) {
                s->dts    = s->cur_frame_dts[i];
                s->pts    = s->cur_frame_pts[i];
                s->pos    = s->cur_frame_pos[i];
                s->offset = s->next_frame_offset - s->cur_frame_offset[i];
            }
            if (remove)
                s->cur_frame_offset[i] = INT64_MAX;
            if (s->cur_offset + off < s->cur_frame_end[i])
                break;
        }
    }
}