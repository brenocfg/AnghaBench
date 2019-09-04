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
typedef  double int64_t ;
struct TYPE_3__ {int start_time_ns; double end_time_ns; double end_offset; double start_offset; } ;
typedef  TYPE_1__ CueDesc ;
typedef  int /*<<< orphan*/  AVFormatContext ;

/* Variables and functions */
 TYPE_1__ get_cue_desc (int /*<<< orphan*/ *,double,double) ; 

__attribute__((used)) static int buffer_size_after_time_downloaded(int64_t time_ns, double search_sec, int64_t bps,
                                             double min_buffer, double* buffer,
                                             double* sec_to_download, AVFormatContext *s,
                                             int64_t cues_start)
{
    double nano_seconds_per_second = 1000000000.0;
    double time_sec = time_ns / nano_seconds_per_second;
    int rv = 0;
    int64_t time_to_search_ns = (int64_t)(search_sec * nano_seconds_per_second);
    int64_t end_time_ns = time_ns + time_to_search_ns;
    double sec_downloaded = 0.0;
    CueDesc desc_curr = get_cue_desc(s, time_ns, cues_start);
    if (desc_curr.start_time_ns == -1)
      return -1;
    *sec_to_download = 0.0;

    // Check for non cue start time.
    if (time_ns > desc_curr.start_time_ns) {
      int64_t cue_nano = desc_curr.end_time_ns - time_ns;
      double percent = (double)(cue_nano) / (desc_curr.end_time_ns - desc_curr.start_time_ns);
      double cueBytes = (desc_curr.end_offset - desc_curr.start_offset) * percent;
      double timeToDownload = (cueBytes * 8.0) / bps;

      sec_downloaded += (cue_nano / nano_seconds_per_second) - timeToDownload;
      *sec_to_download += timeToDownload;

      // Check if the search ends within the first cue.
      if (desc_curr.end_time_ns >= end_time_ns) {
          double desc_end_time_sec = desc_curr.end_time_ns / nano_seconds_per_second;
          double percent_to_sub = search_sec / (desc_end_time_sec - time_sec);
          sec_downloaded = percent_to_sub * sec_downloaded;
          *sec_to_download = percent_to_sub * *sec_to_download;
      }

      if ((sec_downloaded + *buffer) <= min_buffer) {
          return 1;
      }

      // Get the next Cue.
      desc_curr = get_cue_desc(s, desc_curr.end_time_ns, cues_start);
    }

    while (desc_curr.start_time_ns != -1) {
        int64_t desc_bytes = desc_curr.end_offset - desc_curr.start_offset;
        int64_t desc_ns = desc_curr.end_time_ns - desc_curr.start_time_ns;
        double desc_sec = desc_ns / nano_seconds_per_second;
        double bits = (desc_bytes * 8.0);
        double time_to_download = bits / bps;

        sec_downloaded += desc_sec - time_to_download;
        *sec_to_download += time_to_download;

        if (desc_curr.end_time_ns >= end_time_ns) {
            double desc_end_time_sec = desc_curr.end_time_ns / nano_seconds_per_second;
            double percent_to_sub = search_sec / (desc_end_time_sec - time_sec);
            sec_downloaded = percent_to_sub * sec_downloaded;
            *sec_to_download = percent_to_sub * *sec_to_download;

            if ((sec_downloaded + *buffer) <= min_buffer)
                rv = 1;
            break;
        }

        if ((sec_downloaded + *buffer) <= min_buffer) {
            rv = 1;
            break;
        }

        desc_curr = get_cue_desc(s, desc_curr.end_time_ns, cues_start);
    }
    *buffer = *buffer + sec_downloaded;
    return rv;
}