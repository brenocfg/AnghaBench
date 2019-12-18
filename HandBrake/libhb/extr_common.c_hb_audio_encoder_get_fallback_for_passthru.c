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
struct TYPE_5__ {int codec; } ;
typedef  TYPE_1__ hb_encoder_t ;
struct TYPE_6__ {int gid; } ;
typedef  TYPE_2__ hb_encoder_internal_t ;

/* Variables and functions */
#define  HB_ACODEC_AAC_PASS 132 
#define  HB_ACODEC_AC3_PASS 131 
#define  HB_ACODEC_EAC3_PASS 130 
#define  HB_ACODEC_FLAC_PASS 129 
 int HB_ACODEC_INVALID ; 
#define  HB_ACODEC_MP3_PASS 128 
 int HB_GID_ACODEC_AAC ; 
 int HB_GID_ACODEC_AC3 ; 
 int HB_GID_ACODEC_EAC3 ; 
 int HB_GID_ACODEC_FLAC ; 
 int HB_GID_ACODEC_MP3 ; 
 TYPE_1__* hb_audio_encoder_get_next (TYPE_1__ const*) ; 

int hb_audio_encoder_get_fallback_for_passthru(int passthru)
{
    int gid;
    const hb_encoder_t *audio_encoder = NULL;
    switch (passthru)
    {
        case HB_ACODEC_AAC_PASS:
            gid = HB_GID_ACODEC_AAC;
            break;

        case HB_ACODEC_AC3_PASS:
            gid = HB_GID_ACODEC_AC3;
            break;

        case HB_ACODEC_EAC3_PASS:
            gid = HB_GID_ACODEC_EAC3;
            break;

        case HB_ACODEC_FLAC_PASS:
            gid = HB_GID_ACODEC_FLAC;
            break;

        case HB_ACODEC_MP3_PASS:
            gid = HB_GID_ACODEC_MP3;
            break;

        default:
            return HB_ACODEC_INVALID;
            break;
    }
    while ((audio_encoder = hb_audio_encoder_get_next(audio_encoder)) != NULL)
    {
        if (((hb_encoder_internal_t*)audio_encoder)->gid == gid)
        {
            return audio_encoder->codec;
        }
    }

    // passthru tracks are often the second audio from the same source track
    // if we don't have an encoder matching the passthru codec, return INVALID
    // dropping the track, as well as ensuring that there is at least one
    // audio track in the output is then up to the UIs
    return HB_ACODEC_INVALID;
}