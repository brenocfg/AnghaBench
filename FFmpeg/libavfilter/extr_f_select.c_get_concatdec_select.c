#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ int64_t ;
struct TYPE_6__ {int /*<<< orphan*/  value; } ;
struct TYPE_5__ {int /*<<< orphan*/ * metadata; } ;
typedef  TYPE_1__ AVFrame ;
typedef  TYPE_2__ AVDictionaryEntry ;
typedef  int /*<<< orphan*/  AVDictionary ;

/* Variables and functions */
 double NAN ; 
 TYPE_2__* av_dict_get (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ strtoll (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static double get_concatdec_select(AVFrame *frame, int64_t pts)
{
    AVDictionary *metadata = frame->metadata;
    AVDictionaryEntry *start_time_entry = av_dict_get(metadata, "lavf.concatdec.start_time", NULL, 0);
    AVDictionaryEntry *duration_entry = av_dict_get(metadata, "lavf.concatdec.duration", NULL, 0);
    if (start_time_entry) {
        int64_t start_time = strtoll(start_time_entry->value, NULL, 10);
        if (pts >= start_time) {
            if (duration_entry) {
              int64_t duration = strtoll(duration_entry->value, NULL, 10);
              if (pts < start_time + duration)
                  return -1;
              else
                  return 0;
            }
            return -1;
        }
        return 0;
    }
    return NAN;
}