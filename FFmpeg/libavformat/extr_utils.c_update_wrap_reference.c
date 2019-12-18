#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_6__ ;
typedef  struct TYPE_18__   TYPE_5__ ;
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ int64_t ;
struct TYPE_19__ {int nb_streams; TYPE_2__** streams; int /*<<< orphan*/  correct_ts_overflow; } ;
struct TYPE_18__ {scalar_t__ dts; scalar_t__ pts; } ;
struct TYPE_17__ {scalar_t__ pts_wrap_reference; int pts_wrap_behavior; int nb_stream_indexes; size_t* stream_index; } ;
struct TYPE_14__ {int /*<<< orphan*/  num; int /*<<< orphan*/  den; } ;
struct TYPE_16__ {scalar_t__ pts_wrap_reference; int pts_wrap_bits; int pts_wrap_behavior; TYPE_1__ time_base; } ;
struct TYPE_15__ {scalar_t__ pts_wrap_reference; int pts_wrap_behavior; } ;
typedef  TYPE_3__ AVStream ;
typedef  TYPE_4__ AVProgram ;
typedef  TYPE_5__ AVPacket ;
typedef  TYPE_6__ AVFormatContext ;

/* Variables and functions */
 scalar_t__ AV_NOPTS_VALUE ; 
 int AV_PTS_WRAP_ADD_OFFSET ; 
 int AV_PTS_WRAP_SUB_OFFSET ; 
 int av_find_default_stream_index (TYPE_6__*) ; 
 TYPE_4__* av_find_program_from_stream (TYPE_6__*,TYPE_4__*,int) ; 
 long long av_rescale (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int update_wrap_reference(AVFormatContext *s, AVStream *st, int stream_index, AVPacket *pkt)
{
    int64_t ref = pkt->dts;
    int i, pts_wrap_behavior;
    int64_t pts_wrap_reference;
    AVProgram *first_program;

    if (ref == AV_NOPTS_VALUE)
        ref = pkt->pts;
    if (st->pts_wrap_reference != AV_NOPTS_VALUE || st->pts_wrap_bits >= 63 || ref == AV_NOPTS_VALUE || !s->correct_ts_overflow)
        return 0;
    ref &= (1LL << st->pts_wrap_bits)-1;

    // reference time stamp should be 60 s before first time stamp
    pts_wrap_reference = ref - av_rescale(60, st->time_base.den, st->time_base.num);
    // if first time stamp is not more than 1/8 and 60s before the wrap point, subtract rather than add wrap offset
    pts_wrap_behavior = (ref < (1LL << st->pts_wrap_bits) - (1LL << st->pts_wrap_bits-3)) ||
        (ref < (1LL << st->pts_wrap_bits) - av_rescale(60, st->time_base.den, st->time_base.num)) ?
        AV_PTS_WRAP_ADD_OFFSET : AV_PTS_WRAP_SUB_OFFSET;

    first_program = av_find_program_from_stream(s, NULL, stream_index);

    if (!first_program) {
        int default_stream_index = av_find_default_stream_index(s);
        if (s->streams[default_stream_index]->pts_wrap_reference == AV_NOPTS_VALUE) {
            for (i = 0; i < s->nb_streams; i++) {
                if (av_find_program_from_stream(s, NULL, i))
                    continue;
                s->streams[i]->pts_wrap_reference = pts_wrap_reference;
                s->streams[i]->pts_wrap_behavior = pts_wrap_behavior;
            }
        }
        else {
            st->pts_wrap_reference = s->streams[default_stream_index]->pts_wrap_reference;
            st->pts_wrap_behavior = s->streams[default_stream_index]->pts_wrap_behavior;
        }
    }
    else {
        AVProgram *program = first_program;
        while (program) {
            if (program->pts_wrap_reference != AV_NOPTS_VALUE) {
                pts_wrap_reference = program->pts_wrap_reference;
                pts_wrap_behavior = program->pts_wrap_behavior;
                break;
            }
            program = av_find_program_from_stream(s, program, stream_index);
        }

        // update every program with differing pts_wrap_reference
        program = first_program;
        while (program) {
            if (program->pts_wrap_reference != pts_wrap_reference) {
                for (i = 0; i<program->nb_stream_indexes; i++) {
                    s->streams[program->stream_index[i]]->pts_wrap_reference = pts_wrap_reference;
                    s->streams[program->stream_index[i]]->pts_wrap_behavior = pts_wrap_behavior;
                }

                program->pts_wrap_reference = pts_wrap_reference;
                program->pts_wrap_behavior = pts_wrap_behavior;
            }
            program = av_find_program_from_stream(s, program, stream_index);
        }
    }
    return 1;
}