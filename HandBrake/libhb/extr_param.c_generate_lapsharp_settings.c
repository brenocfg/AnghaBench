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
 int /*<<< orphan*/  hb_value_string (char const*) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  strcasecmp (char const*,char*) ; 

__attribute__((used)) static hb_dict_t * generate_lapsharp_settings(const char *preset,
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
        double strength[2];
        const char *kernel_string[2];

        if (tune == NULL || !strcasecmp(tune, "none"))
        {
            strength[0]      = strength[1]      = 0.2;
            kernel_string[0] = kernel_string[1] = "isolap";
            if (!strcasecmp(preset, "ultralight"))
            {
                strength[0]  = strength[1] = 0.05;
            }
            else if (!strcasecmp(preset, "light"))
            {
                strength[0]  = strength[1] = 0.1;
            }
            else if (!strcasecmp(preset, "strong"))
            {
                strength[0]  = strength[1] = 0.3;
            }
            else if (!strcasecmp(preset, "stronger"))
            {
                strength[0]  = strength[1] = 0.5;
            }
            else if (!strcasecmp(preset, "verystrong"))
            {
                strength[0]  = strength[1] = 1.1;
            }
        }
        else if (!strcasecmp(tune, "film"))
        {
            strength[0]      = 0.2;  strength[1] = 0.12;
            kernel_string[0] = kernel_string[1]  = "isolap";
            if (!strcasecmp(preset, "ultralight"))
            {
                strength[0]  = 0.05; strength[1] = 0.03;
            }
            else if (!strcasecmp(preset, "light"))
            {
                strength[0]  = 0.1;  strength[1] = 0.06;
            }
            else if (!strcasecmp(preset, "strong"))
            {
                strength[0]  = 0.3;  strength[1] = 0.2;
            }
            else if (!strcasecmp(preset, "stronger"))
            {
                strength[0]  = 0.5;  strength[1] = 0.3;
            }
            else if (!strcasecmp(preset, "verystrong"))
            {
                strength[0]  = 1.1;  strength[1] = 0.65;
            }
        }
        else if (!strcasecmp(tune, "grain"))
        {
            strength[0]      = 0.2; strength[1] = 0.1;
            kernel_string[0] = kernel_string[1] = "isolog";
            if (!strcasecmp(preset, "ultralight"))
            {
                strength[0] = 0.05; strength[1] = 0.025;
            }
            else if (!strcasecmp(preset, "light"))
            {
                strength[0] = 0.1;  strength[1] = 0.05;
            }
            else if (!strcasecmp(preset, "strong"))
            {
                strength[0] = 0.3;  strength[1] = 0.15;
            }
            else if (!strcasecmp(preset, "stronger"))
            {
                strength[0] = 0.5;  strength[1] = 0.25;
            }
            else if (!strcasecmp(preset, "verystrong"))
            {
                strength[0] = 1.1;  strength[1] = 0.55;
            }
        }
        else if (!strcasecmp(tune, "animation"))
        {
            strength[0]      = 0.15; strength[1]   = 0.09;
            kernel_string[0] = kernel_string[1]    = "isolap";
            if (!strcasecmp(preset, "ultralight"))
            {
                strength[0]  = 0.0375; strength[1] = 0.0225;
            }
            else if (!strcasecmp(preset, "light"))
            {
                strength[0]  = 0.075;  strength[1] = 0.05625;
            }
            else if (!strcasecmp(preset, "strong"))
            {
                strength[0]  = 0.225;  strength[1] = 0.15;
            }
            else if (!strcasecmp(preset, "stronger"))
            {
                strength[0]  = 0.375;  strength[1] = 0.225;
            }
            else if (!strcasecmp(preset, "verystrong"))
            {
                strength[0]  = 0.75;  strength[1] = 0.45;
            }
        }
        else if (!strcasecmp(tune, "sprite"))
        {
            strength[0]      = strength[1]      = 0.15;
            kernel_string[0] = kernel_string[1] = "lap";
            if (!strcasecmp(preset, "ultralight"))
            {
                strength[0]  = strength[1]      = 0.0375;
            }
            else if (!strcasecmp(preset, "light"))
            {
                strength[0]  = strength[1]      = 0.075;
            }
            else if (!strcasecmp(preset, "strong"))
            {
                strength[0]  = strength[1]      = 0.225;
            }
            else if (!strcasecmp(preset, "stronger"))
            {
                strength[0]  = strength[1]      = 0.375;
            }
            else if (!strcasecmp(preset, "verystrong"))
            {
                strength[0]  = strength[1]      = 0.75;
            }
        }
        else
        {
            fprintf(stderr, "Unrecognized lapsharp tune (%s).\n", tune);
            return NULL;
        }

        settings = hb_dict_init();
        hb_dict_set(settings, "y-strength", hb_value_double(strength[0]));
        hb_dict_set(settings, "y-kernel",   hb_value_string(kernel_string[0]));

        hb_dict_set(settings, "cb-strength", hb_value_double(strength[1]));
        hb_dict_set(settings, "cb-kernel",   hb_value_string(kernel_string[1]));
    }
    else
    {
        settings = hb_parse_filter_settings(preset);
        if (tune != NULL)
        {
            fprintf(stderr, "Custom lapsharp parameters specified; ignoring lapsharp tune (%s).\n", tune);
        }
    }

    return settings;
}