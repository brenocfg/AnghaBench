#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  hb_chan_map_t ;
struct TYPE_5__ {scalar_t__ remap_needed; int /*<<< orphan*/ * channel_map_out; int /*<<< orphan*/ * channel_map_in; int /*<<< orphan*/ * remap; } ;
typedef  TYPE_1__ hb_audio_remap_t ;
typedef  enum AVSampleFormat { ____Placeholder_AVSampleFormat } AVSampleFormat ;

/* Variables and functions */
#define  AV_SAMPLE_FMT_DBL 137 
#define  AV_SAMPLE_FMT_DBLP 136 
#define  AV_SAMPLE_FMT_FLT 135 
#define  AV_SAMPLE_FMT_FLTP 134 
#define  AV_SAMPLE_FMT_S16 133 
#define  AV_SAMPLE_FMT_S16P 132 
#define  AV_SAMPLE_FMT_S32 131 
#define  AV_SAMPLE_FMT_S32P 130 
#define  AV_SAMPLE_FMT_U8 129 
#define  AV_SAMPLE_FMT_U8P 128 
 int /*<<< orphan*/  av_get_sample_fmt_name (int) ; 
 TYPE_1__* calloc (int,int) ; 
 int /*<<< orphan*/  hb_audio_remap_free (TYPE_1__*) ; 
 int /*<<< orphan*/  hb_error (char*,...) ; 
 int /*<<< orphan*/  remap_dbl_interleaved ; 
 int /*<<< orphan*/  remap_flt_interleaved ; 
 int /*<<< orphan*/  remap_planar ; 
 int /*<<< orphan*/  remap_s16_interleaved ; 
 int /*<<< orphan*/  remap_s32_interleaved ; 
 int /*<<< orphan*/  remap_u8_interleaved ; 

hb_audio_remap_t* hb_audio_remap_init(enum AVSampleFormat sample_fmt,
                                      hb_chan_map_t *channel_map_out,
                                      hb_chan_map_t *channel_map_in)
{
    hb_audio_remap_t *remap = calloc(1, sizeof(hb_audio_remap_t));
    if (remap == NULL)
    {
        hb_error("hb_audio_remap_init: failed to allocate remap");
        goto fail;
    }

    // sample format
    switch (sample_fmt)
    {
        case AV_SAMPLE_FMT_U8P:
        case AV_SAMPLE_FMT_S16P:
        case AV_SAMPLE_FMT_S32P:
        case AV_SAMPLE_FMT_FLTP:
        case AV_SAMPLE_FMT_DBLP:
            remap->remap = &remap_planar;
            break;

        case AV_SAMPLE_FMT_U8:
            remap->remap = &remap_u8_interleaved;
            break;

        case AV_SAMPLE_FMT_S16:
            remap->remap = &remap_s16_interleaved;
            break;

        case AV_SAMPLE_FMT_S32:
            remap->remap = &remap_s32_interleaved;
            break;

        case AV_SAMPLE_FMT_FLT:
            remap->remap = &remap_flt_interleaved;
            break;

        case AV_SAMPLE_FMT_DBL:
            remap->remap = &remap_dbl_interleaved;
            break;

        default:
            hb_error("hb_audio_remap_init: unsupported sample format '%s'",
                     av_get_sample_fmt_name(sample_fmt));
            goto fail;
    }

    // input/output channel order
    if (channel_map_in == NULL || channel_map_out == NULL)
    {
        hb_error("hb_audio_remap_init: invalid channel map(s)");
        goto fail;
    }
    remap->channel_map_in  = channel_map_in;
    remap->channel_map_out = channel_map_out;

    // remap can't be done until the channel layout has been set
    remap->remap_needed = 0;

    return remap;

fail:
    hb_audio_remap_free(remap);
    return NULL;
}