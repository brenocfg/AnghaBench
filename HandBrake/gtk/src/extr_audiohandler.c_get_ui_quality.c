#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  scalar_t__ gdouble ;
typedef  int /*<<< orphan*/  GhbValue ;

/* Variables and functions */
 scalar_t__ HB_INVALID_AUDIO_QUALITY ; 
 scalar_t__ get_quality (int,scalar_t__) ; 
 scalar_t__ ghb_dict_get_double (int /*<<< orphan*/ *,char*) ; 
 int ghb_settings_audio_encoder_codec (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static gdouble get_ui_quality(GhbValue *settings)
{
    int codec = ghb_settings_audio_encoder_codec(settings, "Encoder");
    gdouble quality = ghb_dict_get_double(settings, "Quality");
    if (quality == HB_INVALID_AUDIO_QUALITY)
    {
        return quality;
    }
    return get_quality(codec, quality);
}