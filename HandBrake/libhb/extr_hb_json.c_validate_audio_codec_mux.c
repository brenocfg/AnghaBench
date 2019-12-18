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
struct TYPE_4__ {int codec; int muxers; int /*<<< orphan*/  short_name; } ;
typedef  TYPE_1__ hb_encoder_t ;

/* Variables and functions */
 int HB_ACODEC_NONE ; 
 TYPE_1__* hb_audio_encoder_get_next (TYPE_1__ const*) ; 
 int /*<<< orphan*/  hb_container_get_short_name (int) ; 
 int /*<<< orphan*/  hb_error (char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int validate_audio_codec_mux(int codec, int mux, int track)
{
    const hb_encoder_t *enc = NULL;
    while ((enc = hb_audio_encoder_get_next(enc)) != NULL)
    {
        if ((enc->codec == codec) && (enc->muxers & mux) == 0)
        {
            if (codec != HB_ACODEC_NONE)
            {
                hb_error("track %d: incompatible encoder '%s' for muxer '%s'",
                         track + 1, enc->short_name,
                         hb_container_get_short_name(mux));
            }
            return -1;
        }
    }
    return 0;
}