#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int allocated_channels; int channels; int planes; scalar_t__ is_planar; } ;
typedef  TYPE_1__ AudioData ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int AVRESAMPLE_MAX_CHANNELS ; 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  calc_ptr_alignment (TYPE_1__*) ; 

int ff_audio_data_set_channels(AudioData *a, int channels)
{
    if (channels < 1 || channels > AVRESAMPLE_MAX_CHANNELS ||
        channels > a->allocated_channels)
        return AVERROR(EINVAL);

    a->channels  = channels;
    a->planes    = a->is_planar ? channels : 1;

    calc_ptr_alignment(a);

    return 0;
}