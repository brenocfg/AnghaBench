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
typedef  int gboolean ;
typedef  int /*<<< orphan*/  GhbValue ;

/* Variables and functions */
 double HB_INVALID_AUDIO_QUALITY ; 
 int /*<<< orphan*/ * ghb_dict_get (int /*<<< orphan*/  const*,char*) ; 
 double ghb_dict_get_double (int /*<<< orphan*/  const*,char*) ; 
 int ghb_dict_get_int (int /*<<< orphan*/  const*,char*) ; 

gboolean ghb_audio_quality_enabled(const GhbValue *asettings)
{
    int        bitrate;
    double     quality;
    GhbValue * val;

    bitrate = ghb_dict_get_int(asettings, "Bitrate");
    quality = ghb_dict_get_double(asettings, "Quality");
    val     = ghb_dict_get(asettings, "Quality");

    return !(bitrate > 0 || val == NULL || quality == HB_INVALID_AUDIO_QUALITY);
}