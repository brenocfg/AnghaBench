#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_10__ {TYPE_1__* pb; } ;
struct TYPE_9__ {int sample_rate; int ext_sample_rate; } ;
struct TYPE_8__ {int seekable; } ;
typedef  TYPE_2__ MPEG4AudioConfig ;
typedef  TYPE_3__ AVFormatContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int AVIO_SEEKABLE_NORMAL ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  av_log (TYPE_3__*,int /*<<< orphan*/ ,char*) ; 
 int avpriv_mpeg4audio_get_config2 (TYPE_2__*,int /*<<< orphan*/ *,int,int,TYPE_3__*) ; 

__attribute__((used)) static int get_aac_sample_rates(AVFormatContext *s, uint8_t *extradata, int extradata_size,
                                int *sample_rate, int *output_sample_rate)
{
    MPEG4AudioConfig mp4ac;
    int ret;

    ret = avpriv_mpeg4audio_get_config2(&mp4ac, extradata, extradata_size, 1, s);
    /* Don't abort if the failure is because of missing extradata. Assume in that
     * case a bitstream filter will provide the muxer with the extradata in the
     * first packet.
     * Abort however if s->pb is not seekable, as we would not be able to seek back
     * to write the sample rate elements once the extradata shows up, anyway. */
    if (ret < 0 && (extradata_size || !(s->pb->seekable & AVIO_SEEKABLE_NORMAL))) {
        av_log(s, AV_LOG_ERROR,
               "Error parsing AAC extradata, unable to determine samplerate.\n");
        return AVERROR(EINVAL);
    }

    if (ret < 0) {
        /* This will only happen when this function is called while writing the
         * header and no extradata is available. The space for this element has
         * to be reserved for when this function is called again after the
         * extradata shows up in the first packet, as there's no way to know if
         * output_sample_rate will be different than sample_rate or not. */
        *output_sample_rate = *sample_rate;
    } else {
        *sample_rate        = mp4ac.sample_rate;
        *output_sample_rate = mp4ac.ext_sample_rate;
    }
    return 0;
}