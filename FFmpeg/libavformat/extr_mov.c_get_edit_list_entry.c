#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ int64_t ;
struct TYPE_8__ {int /*<<< orphan*/  fc; } ;
struct TYPE_7__ {unsigned int elst_count; int /*<<< orphan*/  time_scale; TYPE_1__* elst_data; } ;
struct TYPE_6__ {scalar_t__ time; scalar_t__ duration; } ;
typedef  TYPE_2__ MOVStreamContext ;
typedef  TYPE_3__ MOVContext ;

/* Variables and functions */
 scalar_t__ av_rescale (scalar_t__,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  avpriv_request_sample (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int get_edit_list_entry(MOVContext *mov,
                               const MOVStreamContext *msc,
                               unsigned int edit_list_index,
                               int64_t *edit_list_media_time,
                               int64_t *edit_list_duration,
                               int64_t global_timescale)
{
    if (edit_list_index == msc->elst_count) {
        return 0;
    }
    *edit_list_media_time = msc->elst_data[edit_list_index].time;
    *edit_list_duration = msc->elst_data[edit_list_index].duration;

    /* duration is in global timescale units;convert to msc timescale */
    if (global_timescale == 0) {
      avpriv_request_sample(mov->fc, "Support for mvhd.timescale = 0 with editlists");
      return 0;
    }
    *edit_list_duration = av_rescale(*edit_list_duration, msc->time_scale,
                                     global_timescale);
    return 1;
}