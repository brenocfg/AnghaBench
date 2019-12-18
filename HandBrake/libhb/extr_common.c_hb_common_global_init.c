#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_34__   TYPE_9__ ;
typedef  struct TYPE_33__   TYPE_7__ ;
typedef  struct TYPE_32__   TYPE_6__ ;
typedef  struct TYPE_31__   TYPE_5__ ;
typedef  struct TYPE_30__   TYPE_4__ ;
typedef  struct TYPE_29__   TYPE_3__ ;
typedef  struct TYPE_28__   TYPE_2__ ;
typedef  struct TYPE_27__   TYPE_1__ ;
typedef  struct TYPE_26__   TYPE_19__ ;
typedef  struct TYPE_25__   TYPE_18__ ;
typedef  struct TYPE_24__   TYPE_17__ ;
typedef  struct TYPE_23__   TYPE_14__ ;
typedef  struct TYPE_22__   TYPE_13__ ;
typedef  struct TYPE_21__   TYPE_12__ ;
typedef  struct TYPE_20__   TYPE_10__ ;

/* Type definitions */
struct TYPE_27__ {int /*<<< orphan*/ * next; } ;
typedef  TYPE_1__ hb_rate_internal_t ;
struct TYPE_28__ {int /*<<< orphan*/ * next; } ;
typedef  TYPE_2__ hb_mixdown_internal_t ;
struct TYPE_29__ {TYPE_7__* next; } ;
typedef  TYPE_3__ hb_encoder_internal_t ;
struct TYPE_30__ {int /*<<< orphan*/ * next; } ;
typedef  TYPE_4__ hb_dither_internal_t ;
struct TYPE_31__ {TYPE_10__* next; } ;
typedef  TYPE_5__ hb_container_internal_t ;
struct TYPE_33__ {int codec; } ;
struct TYPE_34__ {scalar_t__ gid; TYPE_7__ item; scalar_t__ enabled; } ;
struct TYPE_32__ {int /*<<< orphan*/  item; scalar_t__ enabled; } ;
struct TYPE_26__ {int /*<<< orphan*/  item; scalar_t__ enabled; } ;
struct TYPE_25__ {int /*<<< orphan*/  item; scalar_t__ enabled; } ;
struct TYPE_24__ {scalar_t__ gid; TYPE_7__ item; scalar_t__ enabled; } ;
struct TYPE_23__ {int /*<<< orphan*/  item; scalar_t__ enabled; } ;
struct TYPE_22__ {int /*<<< orphan*/  item; scalar_t__ enabled; } ;
struct TYPE_20__ {int format; } ;
struct TYPE_21__ {scalar_t__ gid; TYPE_10__ item; scalar_t__ enabled; } ;

/* Variables and functions */
 int HB_ACODEC_MASK ; 
 scalar_t__ HB_GID_ACODEC_AAC ; 
 scalar_t__ HB_GID_ACODEC_AAC_HE ; 
 int HB_MUX_MASK ; 
 int HB_VCODEC_MASK ; 
 TYPE_19__* hb_audio_bitrates ; 
 int hb_audio_bitrates_count ; 
 int /*<<< orphan*/ * hb_audio_bitrates_first_item ; 
 int /*<<< orphan*/ * hb_audio_bitrates_last_item ; 
 TYPE_18__* hb_audio_dithers ; 
 int hb_audio_dithers_count ; 
 int /*<<< orphan*/ * hb_audio_dithers_first_item ; 
 int /*<<< orphan*/ * hb_audio_dithers_last_item ; 
 scalar_t__ hb_audio_encoder_is_enabled (int) ; 
 TYPE_17__* hb_audio_encoders ; 
 int hb_audio_encoders_count ; 
 TYPE_7__* hb_audio_encoders_first_item ; 
 TYPE_7__* hb_audio_encoders_last_item ; 
 TYPE_14__* hb_audio_mixdowns ; 
 int hb_audio_mixdowns_count ; 
 int /*<<< orphan*/ * hb_audio_mixdowns_first_item ; 
 int /*<<< orphan*/ * hb_audio_mixdowns_last_item ; 
 TYPE_13__* hb_audio_rates ; 
 int hb_audio_rates_count ; 
 int /*<<< orphan*/ * hb_audio_rates_first_item ; 
 int /*<<< orphan*/ * hb_audio_rates_last_item ; 
 scalar_t__ hb_container_is_enabled (int) ; 
 TYPE_12__* hb_containers ; 
 int hb_containers_count ; 
 TYPE_10__* hb_containers_first_item ; 
 TYPE_10__* hb_containers_last_item ; 
 scalar_t__ hb_video_encoder_is_enabled (int,int) ; 
 TYPE_9__* hb_video_encoders ; 
 int hb_video_encoders_count ; 
 TYPE_7__* hb_video_encoders_first_item ; 
 TYPE_7__* hb_video_encoders_last_item ; 
 TYPE_6__* hb_video_rates ; 
 int hb_video_rates_count ; 
 int /*<<< orphan*/ * hb_video_rates_first_item ; 
 int /*<<< orphan*/ * hb_video_rates_last_item ; 

void hb_common_global_init(int disable_hardware)
{
    static int common_init_done = 0;
    if (common_init_done)
        return;

    int i, j;

    // video framerates
    for (i = 0; i < hb_video_rates_count; i++)
    {
        if (hb_video_rates[i].enabled)
        {
            if (hb_video_rates_first_item == NULL)
            {
                hb_video_rates_first_item = &hb_video_rates[i].item;
            }
            else
            {
                ((hb_rate_internal_t*)hb_video_rates_last_item)->next =
                    &hb_video_rates[i].item;
            }
            hb_video_rates_last_item = &hb_video_rates[i].item;
        }
    }
    // fallbacks are static for now (no setup required)

    // audio samplerates
    for (i = 0; i < hb_audio_rates_count; i++)
    {
        if (hb_audio_rates[i].enabled)
        {
            if (hb_audio_rates_first_item == NULL)
            {
                hb_audio_rates_first_item = &hb_audio_rates[i].item;
            }
            else
            {
                ((hb_rate_internal_t*)hb_audio_rates_last_item)->next =
                    &hb_audio_rates[i].item;
            }
            hb_audio_rates_last_item = &hb_audio_rates[i].item;
        }
    }
    // fallbacks are static for now (no setup required)

    // audio bitrates
    for (i = 0; i < hb_audio_bitrates_count; i++)
    {
        if (hb_audio_bitrates[i].enabled)
        {
            if (hb_audio_bitrates_first_item == NULL)
            {
                hb_audio_bitrates_first_item = &hb_audio_bitrates[i].item;
            }
            else
            {
                ((hb_rate_internal_t*)hb_audio_bitrates_last_item)->next =
                    &hb_audio_bitrates[i].item;
            }
            hb_audio_bitrates_last_item = &hb_audio_bitrates[i].item;
        }
    }
    // fallbacks are static for now (no setup required)

    // audio dithers
    for (i = 0; i < hb_audio_dithers_count; i++)
    {
        if (hb_audio_dithers[i].enabled)
        {
            if (hb_audio_dithers_first_item == NULL)
            {
                hb_audio_dithers_first_item = &hb_audio_dithers[i].item;
            }
            else
            {
                ((hb_dither_internal_t*)hb_audio_dithers_last_item)->next =
                    &hb_audio_dithers[i].item;
            }
            hb_audio_dithers_last_item = &hb_audio_dithers[i].item;
        }
    }
    // fallbacks are static for now (no setup required)

    // audio mixdowns
    for (i = 0; i < hb_audio_mixdowns_count; i++)
    {
        if (hb_audio_mixdowns[i].enabled)
        {
            if (hb_audio_mixdowns_first_item == NULL)
            {
                hb_audio_mixdowns_first_item = &hb_audio_mixdowns[i].item;
            }
            else
            {
                ((hb_mixdown_internal_t*)hb_audio_mixdowns_last_item)->next =
                    &hb_audio_mixdowns[i].item;
            }
            hb_audio_mixdowns_last_item = &hb_audio_mixdowns[i].item;
        }
    }
    // fallbacks are static for now (no setup required)

    // video encoders
    for (i = 0; i < hb_video_encoders_count; i++)
    {
        if (hb_video_encoders[i].enabled)
        {
            // we still need to check
            hb_video_encoders[i].enabled =
                hb_video_encoder_is_enabled(hb_video_encoders[i].item.codec, disable_hardware);
        }
        if (hb_video_encoders[i].enabled)
        {
            if (hb_video_encoders_first_item == NULL)
            {
                hb_video_encoders_first_item = &hb_video_encoders[i].item;
            }
            else
            {
                ((hb_encoder_internal_t*)hb_video_encoders_last_item)->next =
                    &hb_video_encoders[i].item;
            }
            hb_video_encoders_last_item = &hb_video_encoders[i].item;
        }
    }
    // setup fallbacks
    for (i = 0; i < hb_video_encoders_count; i++)
    {
        if (!hb_video_encoders[i].enabled)
        {
            if ((hb_video_encoders[i].item.codec & HB_VCODEC_MASK) &&
                (hb_video_encoder_is_enabled(hb_video_encoders[i].item.codec, disable_hardware)))
            {
                // we have a specific fallback and it's enabled
                continue;
            }
            for (j = 0; j < hb_video_encoders_count; j++)
            {
                if (hb_video_encoders[j].enabled &&
                    hb_video_encoders[j].gid == hb_video_encoders[i].gid)
                {
                    hb_video_encoders[i].item.codec = hb_video_encoders[j].item.codec;
                    break;
                }
            }
        }
    }

    // audio encoders
    for (i = 0; i < hb_audio_encoders_count; i++)
    {
        if (hb_audio_encoders[i].enabled)
        {
            // we still need to check
            hb_audio_encoders[i].enabled =
                hb_audio_encoder_is_enabled(hb_audio_encoders[i].item.codec);
        }
        if (hb_audio_encoders[i].enabled)
        {
            if (hb_audio_encoders_first_item == NULL)
            {
                hb_audio_encoders_first_item = &hb_audio_encoders[i].item;
            }
            else
            {
                ((hb_encoder_internal_t*)hb_audio_encoders_last_item)->next =
                    &hb_audio_encoders[i].item;
            }
            hb_audio_encoders_last_item = &hb_audio_encoders[i].item;
        }
    }
    // setup fallbacks
    for (i = 0; i < hb_audio_encoders_count; i++)
    {
        if (!hb_audio_encoders[i].enabled)
        {
            if ((hb_audio_encoders[i].item.codec & HB_ACODEC_MASK) &&
                (hb_audio_encoder_is_enabled(hb_audio_encoders[i].item.codec)))
            {
                // we have a specific fallback and it's enabled
                continue;
            }
            for (j = 0; j < hb_audio_encoders_count; j++)
            {
                if (hb_audio_encoders[j].enabled &&
                    hb_audio_encoders[j].gid == hb_audio_encoders[i].gid)
                {
                    hb_audio_encoders[i].item.codec = hb_audio_encoders[j].item.codec;
                    break;
                }
            }
            if (hb_audio_encoders[i].gid == HB_GID_ACODEC_AAC_HE)
            {
                // try to find an AAC fallback if no HE-AAC encoder is available
                for (j = 0; j < hb_audio_encoders_count; j++)
                {
                    if (hb_audio_encoders[j].enabled &&
                        hb_audio_encoders[j].gid == HB_GID_ACODEC_AAC)
                    {
                        hb_audio_encoders[i].item.codec = hb_audio_encoders[j].item.codec;
                        break;
                    }
                }
            }
        }
    }

    // video containers
    for (i = 0; i < hb_containers_count; i++)
    {
        if (hb_containers[i].enabled)
        {
            // we still need to check
            hb_containers[i].enabled =
                hb_container_is_enabled(hb_containers[i].item.format);
        }
        if (hb_containers[i].enabled)
        {
            if (hb_containers_first_item == NULL)
            {
                hb_containers_first_item = &hb_containers[i].item;
            }
            else
            {
                ((hb_container_internal_t*)hb_containers_last_item)->next =
                    &hb_containers[i].item;
            }
            hb_containers_last_item = &hb_containers[i].item;
        }
    }
    // setup fallbacks
    for (i = 0; i < hb_containers_count; i++)
    {
        if (!hb_containers[i].enabled)
        {
            if ((hb_containers[i].item.format & HB_MUX_MASK) &&
                (hb_container_is_enabled(hb_containers[i].item.format)))
            {
                // we have a specific fallback and it's enabled
                continue;
            }
            for (j = 0; j < hb_containers_count; j++)
            {
                if (hb_containers[j].enabled &&
                    hb_containers[j].gid == hb_containers[i].gid)
                {
                    hb_containers[i].item.format = hb_containers[j].item.format;
                    break;
                }
            }
        }
    }

    // we're done, yay!
    common_init_done = 1;
}