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
typedef  int /*<<< orphan*/  hb_dict_t ;

/* Variables and functions */
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char const*) ; 
 int /*<<< orphan*/ * hb_dict_init () ; 
 int /*<<< orphan*/  hb_dict_set (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * hb_parse_filter_settings (char const*) ; 
 int /*<<< orphan*/  hb_value_double (double) ; 
 int /*<<< orphan*/  hb_value_int (int) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  strcasecmp (char const*,char*) ; 

__attribute__((used)) static hb_dict_t * generate_chroma_smooth_settings(const char *preset,
                                                   const char *tune,
                                                   const char *custom)
{
    hb_dict_t * settings;

    if (preset == NULL)
        return NULL;

    if (!strcasecmp(preset, "custom"))
    {
        return hb_parse_filter_settings(custom);
    }
    if (!strcasecmp(preset, "ultralight") ||
        !strcasecmp(preset, "light") ||
        !strcasecmp(preset, "medium") ||
        !strcasecmp(preset, "strong") ||
        !strcasecmp(preset, "stronger") ||
        !strcasecmp(preset, "verystrong"))
    {
        double strength;
        int    size;

        // Strength
        if ((tune == NULL || !strcasecmp(tune, "none")) ||
           (!strcasecmp(tune, "tiny"))   ||
           (!strcasecmp(tune, "small"))  ||
           (!strcasecmp(tune, "medium")) ||
           (!strcasecmp(tune, "wide"))   ||
           (!strcasecmp(tune, "verywide")))
        {
            strength = 1.2;
            if (!strcasecmp(preset, "ultralight"))
            {
                strength = 0.4;
            }
            else if (!strcasecmp(preset, "light"))
            {
                strength = 0.8;
            }
            else if (!strcasecmp(preset, "strong"))
            {
                strength = 1.6;
            }
            else if (!strcasecmp(preset, "stronger"))
            {
                strength = 2.0;
            }
            else if (!strcasecmp(preset, "verystrong"))
            {
                strength = 2.4;
            }
        }
        else
        {
            fprintf(stderr, "Unrecognized chroma smooth tune (%s).\n", tune);
            return NULL;
        }

        // Size
        if (tune == NULL || tune[0] == 0 ||
            !strcasecmp(tune, "none") || !strcasecmp(tune, "medium"))
        {
            size = 7;
        }
        else if (!strcasecmp(tune, "tiny"))
        {
            size = 3;
        }
        else if (!strcasecmp(tune, "small"))
        {
            size = 5;
        }
        else if (!strcasecmp(tune, "wide"))
        {
            size = 9;
        }
        else if (!strcasecmp(tune, "verywide"))
        {
            size = 11;
        }
        else
        {
            fprintf(stderr, "Unrecognized chroma smooth tune (%s).\n", tune);
            return NULL;
        }

        settings = hb_dict_init();
        hb_dict_set(settings, "cb-strength", hb_value_double(strength));
        hb_dict_set(settings, "cb-size",     hb_value_int(size));
    }
    else
    {
        settings = hb_parse_filter_settings(preset);
        if (tune != NULL)
        {
            fprintf(stderr, "Custom chroma smooth parameters specified; ignoring chroma smooth tune (%s).\n", tune);
        }
    }

    return settings;
}