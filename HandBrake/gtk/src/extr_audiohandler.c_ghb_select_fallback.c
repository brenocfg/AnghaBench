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
struct TYPE_3__ {int /*<<< orphan*/  format; } ;
typedef  TYPE_1__ hb_container_t ;
typedef  scalar_t__ gint ;
typedef  int /*<<< orphan*/  GhbValue ;

/* Variables and functions */
 int HB_ACODEC_PASS_FLAG ; 
 char* ghb_dict_get_string (int /*<<< orphan*/ *,char*) ; 
 TYPE_1__* ghb_lookup_container_by_name (char const*) ; 
 scalar_t__ ghb_settings_audio_encoder_codec (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ hb_audio_encoder_get_fallback_for_passthru (int) ; 
 int hb_autopassthru_get_encoder (int,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 

int ghb_select_fallback(GhbValue *settings, int acodec)
{
    gint fallback = 0;

    if (acodec & HB_ACODEC_PASS_FLAG)
    {
        fallback = hb_audio_encoder_get_fallback_for_passthru(acodec);
        if (fallback != 0)
        {
            return fallback;
        }
    }
    const char *mux_id;
    const hb_container_t *mux;

    mux_id = ghb_dict_get_string(settings, "FileFormat");
    mux = ghb_lookup_container_by_name(mux_id);

    fallback = ghb_settings_audio_encoder_codec(settings,
                                                "AudioEncoderFallback");
    return hb_autopassthru_get_encoder(acodec, 0, fallback, mux->format);
}