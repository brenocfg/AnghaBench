#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_6__ ;
typedef  struct TYPE_18__   TYPE_5__ ;
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
struct TYPE_17__ {int /*<<< orphan*/  list_audio; int /*<<< orphan*/  mux; int /*<<< orphan*/  acodec_fallback; int /*<<< orphan*/  acodec_copy_mask; } ;
typedef  TYPE_4__ hb_job_t ;
struct TYPE_18__ {int codec; int /*<<< orphan*/  name; } ;
typedef  TYPE_5__ hb_encoder_t ;
struct TYPE_15__ {int codec; int track; scalar_t__ mixdown; scalar_t__ samplerate; scalar_t__ bitrate; scalar_t__ quality; scalar_t__ compression_level; } ;
struct TYPE_14__ {scalar_t__ samplerate; int /*<<< orphan*/  channel_layout; int /*<<< orphan*/  codec; } ;
struct TYPE_16__ {TYPE_2__ out; TYPE_1__ in; } ;
struct TYPE_19__ {TYPE_3__ config; } ;
typedef  TYPE_6__ hb_audio_t ;

/* Variables and functions */
 int HB_ACODEC_AUTO_PASS ; 
 int HB_ACODEC_INVALID ; 
 int HB_ACODEC_NONE ; 
 int HB_ACODEC_PASS_FLAG ; 
 scalar_t__ HB_INVALID_AUDIO_QUALITY ; 
 scalar_t__ hb_audio_bitrate_get_best (int,scalar_t__,scalar_t__,scalar_t__) ; 
 scalar_t__ hb_audio_bitrate_get_default (int,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  hb_audio_close (TYPE_6__**) ; 
 scalar_t__ hb_audio_compression_get_best (int,scalar_t__) ; 
 scalar_t__ hb_audio_compression_get_default (int) ; 
 TYPE_5__* hb_audio_encoder_get_next (TYPE_5__ const*) ; 
 scalar_t__ hb_audio_quality_get_best (int,scalar_t__) ; 
 scalar_t__ hb_audio_quality_get_default (int) ; 
 scalar_t__ hb_audio_samplerate_find_closest (scalar_t__,int) ; 
 int hb_autopassthru_get_encoder (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hb_autopassthru_print_settings (TYPE_4__*) ; 
 int hb_list_count (int /*<<< orphan*/ ) ; 
 TYPE_6__* hb_list_item (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  hb_list_rem (int /*<<< orphan*/ ,TYPE_6__*) ; 
 int /*<<< orphan*/  hb_log (char*,int,...) ; 
 scalar_t__ hb_mixdown_get_best (int,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ hb_mixdown_get_default (int,int /*<<< orphan*/ ) ; 

void hb_autopassthru_apply_settings(hb_job_t *job)
{
    hb_audio_t *audio;
    int i, already_printed;
    for (i = already_printed = 0; i < hb_list_count(job->list_audio);)
    {
        audio = hb_list_item(job->list_audio, i);
        if (audio->config.out.codec == HB_ACODEC_AUTO_PASS)
        {
            if (!already_printed)
                hb_autopassthru_print_settings(job);
            already_printed = 1;
            audio->config.out.codec = hb_autopassthru_get_encoder(audio->config.in.codec,
                                                                  job->acodec_copy_mask,
                                                                  job->acodec_fallback,
                                                                  job->mux);
            if (audio->config.out.codec == HB_ACODEC_NONE ||
                audio->config.out.codec == HB_ACODEC_INVALID)
            {
                hb_log("Auto Passthru: passthru not possible and no valid fallback specified, dropping track %d",
                       audio->config.out.track );
                hb_list_rem(job->list_audio, audio);
                hb_audio_close(&audio);
                continue;
            }
            if (!(audio->config.out.codec & HB_ACODEC_PASS_FLAG))
            {
                hb_log("Auto Passthru: passthru not possible for track %d, using fallback",
                       audio->config.out.track);
                if (audio->config.out.mixdown <= 0)
                {
                    audio->config.out.mixdown =
                        hb_mixdown_get_default(audio->config.out.codec,
                                               audio->config.in.channel_layout);
                }
                else
                {
                    audio->config.out.mixdown =
                        hb_mixdown_get_best(audio->config.out.codec,
                                            audio->config.in.channel_layout,
                                            audio->config.out.mixdown);
                }
                if (audio->config.out.samplerate <= 0)
                    audio->config.out.samplerate = audio->config.in.samplerate;
                audio->config.out.samplerate =
                    hb_audio_samplerate_find_closest(
                        audio->config.out.samplerate, audio->config.out.codec);
                int quality_not_allowed =
                    hb_audio_quality_get_default(audio->config.out.codec)
                            == HB_INVALID_AUDIO_QUALITY;
                if (audio->config.out.bitrate > 0)
                {
                    // Use best bitrate
                    audio->config.out.bitrate =
                        hb_audio_bitrate_get_best(audio->config.out.codec,
                                                  audio->config.out.bitrate,
                                                  audio->config.out.samplerate,
                                                  audio->config.out.mixdown);
                }
                else if (quality_not_allowed ||
                         audio->config.out.quality != HB_INVALID_AUDIO_QUALITY)
                {
                    // Use default bitrate
                    audio->config.out.bitrate =
                        hb_audio_bitrate_get_default(audio->config.out.codec,
                                                 audio->config.out.samplerate,
                                                 audio->config.out.mixdown);
                }
                else
                {
                    // Use best quality
                    audio->config.out.quality =
                        hb_audio_quality_get_best(audio->config.out.codec,
                                                  audio->config.out.quality);
                }
                if (audio->config.out.compression_level < 0)
                {
                    audio->config.out.compression_level =
                        hb_audio_compression_get_default(
                                        audio->config.out.codec);
                }
                else
                {
                    audio->config.out.compression_level =
                        hb_audio_compression_get_best(audio->config.out.codec,
                                        audio->config.out.compression_level);
                }
            }
            else
            {
                const hb_encoder_t *audio_encoder = NULL;
                while ((audio_encoder = hb_audio_encoder_get_next(audio_encoder)) != NULL)
                {
                    if (audio_encoder->codec == audio->config.out.codec)
                    {
                        hb_log("Auto Passthru: using %s for track %d",
                               audio_encoder->name,
                               audio->config.out.track);
                        break;
                    }
                }
            }
        }
        /* Adjust output track number, in case we removed one.
         * Output tracks sadly still need to be in sequential order.
         * Note: out.track starts at 1, i starts at 0 */
        audio->config.out.track = ++i;
    }
}