#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  int64_t ;
struct TYPE_17__ {int nb_streams; TYPE_4__** streams; TYPE_3__* priv_data; } ;
struct TYPE_16__ {TYPE_2__* priv_data; int /*<<< orphan*/  time_base; int /*<<< orphan*/  skip_samples; TYPE_1__* index_entries; } ;
struct TYPE_15__ {scalar_t__ seek_individually; } ;
struct TYPE_14__ {int ffindex; int current_sample; int /*<<< orphan*/  start_pad; } ;
struct TYPE_13__ {int /*<<< orphan*/  timestamp; } ;
typedef  TYPE_2__ MOVStreamContext ;
typedef  TYPE_3__ MOVContext ;
typedef  TYPE_4__ AVStream ;
typedef  int /*<<< orphan*/  AVIndexEntry ;
typedef  TYPE_5__ AVFormatContext ;

/* Variables and functions */
 int AVERROR_INVALIDDATA ; 
 int /*<<< orphan*/  av_rescale_q (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mov_current_sample_inc (TYPE_2__*) ; 
 int /*<<< orphan*/  mov_current_sample_set (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * mov_find_next_sample (TYPE_5__*,TYPE_4__**) ; 
 int mov_seek_stream (TYPE_5__*,TYPE_4__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int mov_read_seek(AVFormatContext *s, int stream_index, int64_t sample_time, int flags)
{
    MOVContext *mc = s->priv_data;
    AVStream *st;
    int sample;
    int i;

    if (stream_index >= s->nb_streams)
        return AVERROR_INVALIDDATA;

    st = s->streams[stream_index];
    sample = mov_seek_stream(s, st, sample_time, flags);
    if (sample < 0)
        return sample;

    if (mc->seek_individually) {
        /* adjust seek timestamp to found sample timestamp */
        int64_t seek_timestamp = st->index_entries[sample].timestamp;

        for (i = 0; i < s->nb_streams; i++) {
            int64_t timestamp;
            MOVStreamContext *sc = s->streams[i]->priv_data;
            st = s->streams[i];
            st->skip_samples = (sample_time <= 0) ? sc->start_pad : 0;

            if (stream_index == i)
                continue;

            timestamp = av_rescale_q(seek_timestamp, s->streams[stream_index]->time_base, st->time_base);
            mov_seek_stream(s, st, timestamp, flags);
        }
    } else {
        for (i = 0; i < s->nb_streams; i++) {
            MOVStreamContext *sc;
            st = s->streams[i];
            sc = st->priv_data;
            mov_current_sample_set(sc, 0);
        }
        while (1) {
            MOVStreamContext *sc;
            AVIndexEntry *entry = mov_find_next_sample(s, &st);
            if (!entry)
                return AVERROR_INVALIDDATA;
            sc = st->priv_data;
            if (sc->ffindex == stream_index && sc->current_sample == sample)
                break;
            mov_current_sample_inc(sc);
        }
    }
    return 0;
}