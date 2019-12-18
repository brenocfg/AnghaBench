#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {size_t channels; TYPE_1__* d; } ;
struct TYPE_4__ {scalar_t__* channel_map; size_t audio_data_index; double* audio_data; size_t audio_data_frames; int /*<<< orphan*/ * block_energy_histogram; } ;
typedef  TYPE_2__ FFEBUR128State ;

/* Variables and functions */
 scalar_t__ FF_EBUR128_DUAL_MONO ; 
 scalar_t__ FF_EBUR128_Mm060 ; 
 scalar_t__ FF_EBUR128_Mm090 ; 
 scalar_t__ FF_EBUR128_Mm110 ; 
 scalar_t__ FF_EBUR128_Mp060 ; 
 scalar_t__ FF_EBUR128_Mp090 ; 
 scalar_t__ FF_EBUR128_Mp110 ; 
 scalar_t__ FF_EBUR128_UNUSED ; 
 size_t find_histogram_index (double) ; 
 double* histogram_energy_boundaries ; 

__attribute__((used)) static void ebur128_calc_gating_block(FFEBUR128State * st,
                                      size_t frames_per_block,
                                      double *optional_output)
{
    size_t i, c;
    double sum = 0.0;
    double channel_sum;
    for (c = 0; c < st->channels; ++c) {
        if (st->d->channel_map[c] == FF_EBUR128_UNUSED)
            continue;
        channel_sum = 0.0;
        if (st->d->audio_data_index < frames_per_block * st->channels) {
            for (i = 0; i < st->d->audio_data_index / st->channels; ++i) {
                channel_sum += st->d->audio_data[i * st->channels + c] *
                    st->d->audio_data[i * st->channels + c];
            }
            for (i = st->d->audio_data_frames -
                 (frames_per_block -
                  st->d->audio_data_index / st->channels);
                 i < st->d->audio_data_frames; ++i) {
                channel_sum += st->d->audio_data[i * st->channels + c] *
                    st->d->audio_data[i * st->channels + c];
            }
        } else {
            for (i =
                 st->d->audio_data_index / st->channels - frames_per_block;
                 i < st->d->audio_data_index / st->channels; ++i) {
                channel_sum +=
                    st->d->audio_data[i * st->channels +
                                      c] * st->d->audio_data[i *
                                                             st->channels +
                                                             c];
            }
        }
        if (st->d->channel_map[c] == FF_EBUR128_Mp110 ||
            st->d->channel_map[c] == FF_EBUR128_Mm110 ||
            st->d->channel_map[c] == FF_EBUR128_Mp060 ||
            st->d->channel_map[c] == FF_EBUR128_Mm060 ||
            st->d->channel_map[c] == FF_EBUR128_Mp090 ||
            st->d->channel_map[c] == FF_EBUR128_Mm090) {
            channel_sum *= 1.41;
        } else if (st->d->channel_map[c] == FF_EBUR128_DUAL_MONO) {
            channel_sum *= 2.0;
        }
        sum += channel_sum;
    }
    sum /= (double) frames_per_block;
    if (optional_output) {
        *optional_output = sum;
    } else if (sum >= histogram_energy_boundaries[0]) {
        ++st->d->block_energy_histogram[find_histogram_index(sum)];
    }
}