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
struct TYPE_3__ {int /*<<< orphan*/  SampleFrequencyGranularity; int /*<<< orphan*/  MaximumSampleFrequency; int /*<<< orphan*/  MinimumSampleFrequency; int /*<<< orphan*/  BitsPerSampleGranularity; int /*<<< orphan*/  MaximumBitsPerSample; int /*<<< orphan*/  MinimumBitsPerSample; int /*<<< orphan*/  ChannelsGranularity; int /*<<< orphan*/  MaximumChannels; int /*<<< orphan*/  MinimumChannels; int /*<<< orphan*/  guid; } ;
typedef  TYPE_1__ AUDIO_STREAM_CONFIG_CAPS ;

/* Variables and functions */
 int /*<<< orphan*/  dshowdebug (char*,...) ; 
 int /*<<< orphan*/  ff_printGUID (int /*<<< orphan*/ *) ; 

void ff_print_AUDIO_STREAM_CONFIG_CAPS(const AUDIO_STREAM_CONFIG_CAPS *caps)
{
#if DSHOWDEBUG
    dshowdebug(" AUDIO_STREAM_CONFIG_CAPS\n");
    dshowdebug("  guid\t");
    ff_printGUID(&caps->guid);
    dshowdebug("\n");
    dshowdebug("  MinimumChannels\t%lu\n", caps->MinimumChannels);
    dshowdebug("  MaximumChannels\t%lu\n", caps->MaximumChannels);
    dshowdebug("  ChannelsGranularity\t%lu\n", caps->ChannelsGranularity);
    dshowdebug("  MinimumBitsPerSample\t%lu\n", caps->MinimumBitsPerSample);
    dshowdebug("  MaximumBitsPerSample\t%lu\n", caps->MaximumBitsPerSample);
    dshowdebug("  BitsPerSampleGranularity\t%lu\n", caps->BitsPerSampleGranularity);
    dshowdebug("  MinimumSampleFrequency\t%lu\n", caps->MinimumSampleFrequency);
    dshowdebug("  MaximumSampleFrequency\t%lu\n", caps->MaximumSampleFrequency);
    dshowdebug("  SampleFrequencyGranularity\t%lu\n", caps->SampleFrequencyGranularity);
#endif
}