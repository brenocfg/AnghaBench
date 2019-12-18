#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  mod_bits_per_second ;
typedef  int int64_t ;
struct TYPE_14__ {TYPE_4__** streams; TYPE_2__* priv_data; } ;
struct TYPE_13__ {int nb_index_entries; TYPE_1__* index_entries; } ;
struct TYPE_12__ {int start_time_ns; int end_time_ns; int end_offset; int start_offset; } ;
struct TYPE_11__ {int time_scale; int duration; } ;
struct TYPE_10__ {int timestamp; } ;
typedef  TYPE_2__ MatroskaDemuxContext ;
typedef  TYPE_3__ CueDesc ;
typedef  TYPE_4__ AVStream ;
typedef  TYPE_5__ AVFormatContext ;

/* Variables and functions */
 int buffer_size_after_time_downloaded (int,double,int,double const,double*,double*,TYPE_5__*,int) ; 
 TYPE_3__ get_cue_desc (TYPE_5__*,int,int) ; 

__attribute__((used)) static int64_t webm_dash_manifest_compute_bandwidth(AVFormatContext *s, int64_t cues_start)
{
    MatroskaDemuxContext *matroska = s->priv_data;
    AVStream *st = s->streams[0];
    double bandwidth = 0.0;
    int i;

    for (i = 0; i < st->nb_index_entries; i++) {
        int64_t prebuffer_ns = 1000000000;
        int64_t time_ns = st->index_entries[i].timestamp * matroska->time_scale;
        double nano_seconds_per_second = 1000000000.0;
        int64_t prebuffered_ns = time_ns + prebuffer_ns;
        double prebuffer_bytes = 0.0;
        int64_t temp_prebuffer_ns = prebuffer_ns;
        int64_t pre_bytes, pre_ns;
        double pre_sec, prebuffer, bits_per_second;
        CueDesc desc_beg = get_cue_desc(s, time_ns, cues_start);

        // Start with the first Cue.
        CueDesc desc_end = desc_beg;

        // Figure out how much data we have downloaded for the prebuffer. This will
        // be used later to adjust the bits per sample to try.
        while (desc_end.start_time_ns != -1 && desc_end.end_time_ns < prebuffered_ns) {
            // Prebuffered the entire Cue.
            prebuffer_bytes += desc_end.end_offset - desc_end.start_offset;
            temp_prebuffer_ns -= desc_end.end_time_ns - desc_end.start_time_ns;
            desc_end = get_cue_desc(s, desc_end.end_time_ns, cues_start);
        }
        if (desc_end.start_time_ns == -1) {
            // The prebuffer is larger than the duration.
            if (matroska->duration * matroska->time_scale >= prebuffered_ns)
              return -1;
            bits_per_second = 0.0;
        } else {
            // The prebuffer ends in the last Cue. Estimate how much data was
            // prebuffered.
            pre_bytes = desc_end.end_offset - desc_end.start_offset;
            pre_ns = desc_end.end_time_ns - desc_end.start_time_ns;
            pre_sec = pre_ns / nano_seconds_per_second;
            prebuffer_bytes +=
                pre_bytes * ((temp_prebuffer_ns / nano_seconds_per_second) / pre_sec);

            prebuffer = prebuffer_ns / nano_seconds_per_second;

            // Set this to 0.0 in case our prebuffer buffers the entire video.
            bits_per_second = 0.0;
            do {
                int64_t desc_bytes = desc_end.end_offset - desc_beg.start_offset;
                int64_t desc_ns = desc_end.end_time_ns - desc_beg.start_time_ns;
                double desc_sec = desc_ns / nano_seconds_per_second;
                double calc_bits_per_second = (desc_bytes * 8) / desc_sec;

                // Drop the bps by the percentage of bytes buffered.
                double percent = (desc_bytes - prebuffer_bytes) / desc_bytes;
                double mod_bits_per_second = calc_bits_per_second * percent;

                if (prebuffer < desc_sec) {
                    double search_sec =
                        (double)(matroska->duration * matroska->time_scale) / nano_seconds_per_second;

                    // Add 1 so the bits per second should be a little bit greater than file
                    // datarate.
                    int64_t bps = (int64_t)(mod_bits_per_second) + 1;
                    const double min_buffer = 0.0;
                    double buffer = prebuffer;
                    double sec_to_download = 0.0;

                    int rv = buffer_size_after_time_downloaded(prebuffered_ns, search_sec, bps,
                                                               min_buffer, &buffer, &sec_to_download,
                                                               s, cues_start);
                    if (rv < 0) {
                        return -1;
                    } else if (rv == 0) {
                        bits_per_second = (double)(bps);
                        break;
                    }
                }

                desc_end = get_cue_desc(s, desc_end.end_time_ns, cues_start);
            } while (desc_end.start_time_ns != -1);
        }
        if (bandwidth < bits_per_second) bandwidth = bits_per_second;
    }
    return (int64_t)bandwidth;
}