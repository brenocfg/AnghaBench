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
typedef  int /*<<< orphan*/  gchar ;
typedef  int /*<<< orphan*/  gboolean ;
typedef  int /*<<< orphan*/  GtkWindow ;
typedef  int /*<<< orphan*/  GhbValue ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  GTK_MESSAGE_ERROR ; 
 int HB_FILTER_COMB_DETECT ; 
 int HB_FILTER_DETELECINE ; 
 int HB_FILTER_INVALID ; 
 int HB_FILTER_NLMEANS ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  g_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * g_strdup_printf (int /*<<< orphan*/ ,char const*,...) ; 
 char* ghb_dict_get_string (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  ghb_message_dialog (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int ghb_settings_combo_int (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ hb_validate_filter_preset (int,char const*,char const*,char const*) ; 
 scalar_t__ strcasecmp (char const*,char*) ; 

gboolean
ghb_validate_filters(GhbValue *settings, GtkWindow *parent)
{
    gchar *message;

    // Detelecine
    const char *detel_preset;
    detel_preset = ghb_dict_get_string(settings, "PictureDetelecine");
    if (strcasecmp(detel_preset, "off"))
    {
        const char *detel_custom = NULL;
        int filter_id;

        filter_id = HB_FILTER_DETELECINE;
        detel_custom = ghb_dict_get_string(settings, "PictureDetelecineCustom");
        if (hb_validate_filter_preset(filter_id, detel_preset, NULL,
                                      detel_custom))
        {
            if (detel_custom != NULL)
            {
                message = g_strdup_printf(
                            _("Invalid Detelecine Settings:\n\n"
                              "Preset:\t%s\n"
                              "Custom:\t%s\n"), detel_preset, detel_custom);
            }
            else
            {
                message = g_strdup_printf(
                            _("Invalid Detelecine Settings:\n\n"
                              "Preset:\t%s\n"), detel_preset);
            }
            ghb_message_dialog(parent, GTK_MESSAGE_ERROR,
                               message, _("Cancel"), NULL);
            g_free(message);
            return FALSE;
        }
    }

    // Comb Detect
    const char *comb_preset;
    comb_preset = ghb_dict_get_string(settings, "PictureCombDetectPreset");
    if (strcasecmp(comb_preset, "off"))
    {
        const char *comb_custom = NULL;
        int filter_id;

        filter_id = HB_FILTER_COMB_DETECT;
        comb_custom = ghb_dict_get_string(settings, "PictureCombDetectCustom");
        if (hb_validate_filter_preset(filter_id, comb_preset, NULL,
                                      comb_custom))
        {
            if (comb_custom != NULL && comb_custom[0] != 0)
            {
                message = g_strdup_printf(
                            _("Invalid Comb Detect Settings:\n\n"
                              "Preset:\t%s\n"
                              "Custom:\t%s\n"), comb_preset, comb_custom);
            }
            else
            {
                message = g_strdup_printf(
                            _("Invalid Comb Detect Settings:\n\n"
                              "Preset:\t%s\n"), comb_preset);
            }
            ghb_message_dialog(parent, GTK_MESSAGE_ERROR,
                               message, _("Cancel"), NULL);
            g_free(message);
            return FALSE;
        }
    }

    // Deinterlace
    int filter_id;
    filter_id = ghb_settings_combo_int(settings, "PictureDeinterlaceFilter");
    if (filter_id != HB_FILTER_INVALID)
    {
        const char *deint_filter, *deint_preset, *deint_custom = NULL;

        deint_filter = ghb_dict_get_string(settings,
                                           "PictureDeinterlaceFilter");
        deint_preset = ghb_dict_get_string(settings,
                                           "PictureDeinterlacePreset");
        deint_custom = ghb_dict_get_string(settings,
                                           "PictureDeinterlaceCustom");
        if (hb_validate_filter_preset(filter_id, deint_preset, NULL,
                                      deint_custom))
        {
            if (deint_custom != NULL)
            {
                message = g_strdup_printf(
                            _("Invalid Deinterlace Settings:\n\n"
                              "Filter:\t%s\n"
                              "Preset:\t%s\n"
                              "Custom:\t%s\n"), deint_filter, deint_preset,
                                                deint_custom);
            }
            else
            {
                message = g_strdup_printf(
                            _("Invalid Deinterlace Settings:\n\n"
                              "Filter:\t%s\n"
                              "Preset:\t%s\n"), deint_filter, deint_preset);
            }
            ghb_message_dialog(parent, GTK_MESSAGE_ERROR,
                               message, _("Cancel"), NULL);
            g_free(message);
            return FALSE;
        }
    }

    // Denoise
    filter_id = ghb_settings_combo_int(settings, "PictureDenoiseFilter");
    if (filter_id != HB_FILTER_INVALID)
    {
        const char *denoise_filter, *denoise_preset;
        const char *denoise_tune = NULL, *denoise_custom = NULL;

        denoise_filter = ghb_dict_get_string(settings, "PictureDenoiseFilter");
        denoise_preset = ghb_dict_get_string(settings, "PictureDenoisePreset");
        if (filter_id == HB_FILTER_NLMEANS)
        {
            denoise_tune = ghb_dict_get_string(settings, "PictureDenoiseTune");
        }
        denoise_custom = ghb_dict_get_string(settings, "PictureDenoiseCustom");
        if (hb_validate_filter_preset(filter_id, denoise_preset, denoise_tune,
                                      denoise_custom))
        {
            message = g_strdup_printf(
                        _("Invalid Denoise Settings:\n\n"
                          "Filter:\t%s\n"
                          "Preset:\t%s\n"
                          "Tune:\t%s\n"
                          "Custom:\t%s\n"), denoise_filter, denoise_preset,
                                           denoise_tune, denoise_custom);
            ghb_message_dialog(parent, GTK_MESSAGE_ERROR,
                               message, _("Cancel"), NULL);
            g_free(message);
            return FALSE;
        }
    }

    // Sharpen
    filter_id = ghb_settings_combo_int(settings, "PictureSharpenFilter");
    if (filter_id != HB_FILTER_INVALID)
    {
        const char *sharpen_filter, *sharpen_preset;
        const char *sharpen_tune = NULL, *sharpen_custom = NULL;

        sharpen_filter = ghb_dict_get_string(settings, "PictureSharpenFilter");
        sharpen_preset = ghb_dict_get_string(settings, "PictureSharpenPreset");
        sharpen_tune = ghb_dict_get_string(settings, "PictureSharpenTune");
        sharpen_custom = ghb_dict_get_string(settings, "PictureSharpenCustom");
        if (hb_validate_filter_preset(filter_id, sharpen_preset, sharpen_tune,
                                      sharpen_custom))
        {
            message = g_strdup_printf(
                        _("Invalid Sharpen Settings:\n\n"
                          "Filter:\t%s\n"
                          "Preset:\t%s\n"
                          "Tune:\t%s\n"
                          "Custom:\t%s\n"), sharpen_filter, sharpen_preset,
                                           sharpen_tune, sharpen_custom);
            ghb_message_dialog(parent, GTK_MESSAGE_ERROR,
                               message, _("Cancel"), NULL);
            g_free(message);
            return FALSE;
        }
    }

    return TRUE;
}