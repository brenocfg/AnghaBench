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

__attribute__((used)) static hb_dict_t * generate_nlmeans_settings(const char *preset,
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
        !strcasecmp(preset, "strong"))
    {
        double strength[2],
               origin_tune[2];
        int    patch_size[2],
               range[2],
               frames[2],
               prefilter[2];

        if (tune == NULL || !strcasecmp(tune, "none"))
        {
            strength[0]    = strength[1]    = 6;
            origin_tune[0] = origin_tune[1] = 1;
            patch_size[0]  = patch_size[1]  = 7;
            range[0]       = range[1]       = 3;
            frames[0]      = frames[1]      = 2;
            prefilter[0]   = prefilter[1]   = 0;
            if (!strcasecmp(preset, "ultralight"))
            {
                strength[0] = strength[1] = 1.5;
            }
            else if (!strcasecmp(preset, "light"))
            {
                strength[0] = strength[1] = 3;
            }
            else if (!strcasecmp(preset, "strong"))
            {
                strength[0] = strength[1] = 10;
            }
        }
        else if (!strcasecmp(tune, "film"))
        {
            strength[0]    = 6; strength[1] = 8;
            origin_tune[0] = origin_tune[1] = 0.8;
            patch_size[0]  = patch_size[1]  = 7;
            range[0]       = range[1]       = 3;
            frames[0]      = frames[1]      = 2;
            prefilter[0]   = prefilter[1]   = 0;
            if (!strcasecmp(preset, "ultralight"))
            {
                strength[0]    = 1.5;   strength[1]  = 2.4;
                origin_tune[0] = 0.9; origin_tune[1] = 0.9;
            }
            else if (!strcasecmp(preset, "light"))
            {
                strength[0]    = 3;   strength[1]    = 4;
                origin_tune[0] = 0.9; origin_tune[1] = 0.9;
            }
            else if (!strcasecmp(preset, "strong"))
            {
                strength[0]    = 8;   strength[1]    = 10;
                origin_tune[0] = 0.6; origin_tune[1] = 0.6;
            }
        }
        else if (!strcasecmp(tune, "grain"))
        {
            strength[0]    = 0; strength[1] = 6;
            origin_tune[0] = origin_tune[1] = 0.8;
            patch_size[0]  = patch_size[1]  = 7;
            range[0]       = range[1]       = 3;
            frames[0]      = frames[1]      = 2;
            prefilter[0]   = prefilter[1]   = 0;
            if (!strcasecmp(preset, "ultralight"))
            {
                strength[0]    = 0;   strength[1]    = 2.4;
                origin_tune[0] = 0.9; origin_tune[1] = 0.9;
            }
            else if (!strcasecmp(preset, "light"))
            {
                strength[0]    = 0;   strength[1]    = 3.5;
                origin_tune[0] = 0.9; origin_tune[1] = 0.9;
            }
            else if (!strcasecmp(preset, "strong"))
            {
                strength[0]    = 0;   strength[1]    = 8;
                origin_tune[0] = 0.6; origin_tune[1] = 0.6;
            }
        }
        else if (!strcasecmp(tune, "highmotion"))
        {
            strength[0]    = 6;   strength[1]    = 6;
            origin_tune[0] = 0.8; origin_tune[1] = 0.7;
            patch_size[0]  = 7;   patch_size[1]  = 7;
            range[0]       = 3;   range[1]       = 5;
            frames[0]      = 2;   frames[1]      = 1;
            prefilter[0]   = 0;   prefilter[1]   = 0;
            if (!strcasecmp(preset, "ultralight"))
            {
                strength[0]    = 1.5;   strength[1]  = 2.4;
                origin_tune[0] = 0.9; origin_tune[1] = 0.9;
            }
            else if (!strcasecmp(preset, "light"))
            {
                strength[0]    = 3;   strength[1]    = 3.25;
                origin_tune[0] = 0.9; origin_tune[1] = 0.8;
            }
            else if (!strcasecmp(preset, "strong"))
            {
                strength[0]    = 8;   strength[1]    = 6.75;
                origin_tune[0] = 0.6; origin_tune[1] = 0.5;
            }
        }
        else if (!strcasecmp(tune, "animation"))
        {
            strength[0]    = 5; strength[1] = 4;
            origin_tune[0] = origin_tune[1] = 0.15;
            patch_size[0]  = patch_size[1]  = 5;
            range[0]       = range[1]       = 7;
            frames[0]      = frames[1]      = 4;
            prefilter[0]   = prefilter[1]   = 0;
            if (!strcasecmp(preset, "ultralight"))
            {
                strength[0] = 2.5; strength[1] = 2;
                frames[0]   = 2;   frames[1]   = 2;
            }
            else if (!strcasecmp(preset, "light"))
            {
                strength[0] = 3; strength[1] = 2.25;
                frames[0]   = 3; frames[1]   = 3;
            }
            else if (!strcasecmp(preset, "strong"))
            {
                strength[0] = 10; strength[1] = 8;
            }
        }
        else if (!strcasecmp(tune, "tape"))
        {
            strength[0]    = 3;   strength[1]    = 6;
            origin_tune[0] = 0.8; origin_tune[1] = 0.8;
            patch_size[0]  = 3;   patch_size[1]  = 5;
            range[0]       = 5;   range[1]       = 5;
            frames[0]      = 2;   frames[1]      = 2;
            prefilter[0]   = 0;   prefilter[1]   = 0;
            if (!strcasecmp(preset, "ultralight"))
            {
                strength[0]    = 1.5; strength[1]    = 5;
                origin_tune[0] = 0.9; origin_tune[1] = 0.9;
                frames[0]      = 1;   frames[1]      = 1;
            }
            else if (!strcasecmp(preset, "light"))
            {
                strength[0]    = 2;   strength[1]    = 6;
                origin_tune[0] = 0.9; origin_tune[1] = 0.9;
            }
            else if (!strcasecmp(preset, "strong"))
            {
                strength[0]    = 3.5; strength[1]    = 8;
                origin_tune[0] = 0.6; origin_tune[1] = 0.6;
                patch_size[0]  = 5;   patch_size[1]  = 5;
            }
        }
        else if (!strcasecmp(tune, "sprite"))
        {
            strength[0]    = 3;    strength[1]    = 4;
            origin_tune[0] = 0.15; origin_tune[1] = 0.5;
            patch_size[0]  = 5;    patch_size[1]  = 5;
            range[0]       = 5;    range[1]       = 9;
            frames[0]      = 2;    frames[1]      = 4;
            prefilter[0]   = 0;    prefilter[1]   = 0;
            if (!strcasecmp(preset, "ultralight"))
            {
                strength[0]    = 1.5; strength[1]    = 3;
                range[0]       = 5;   range[1]       = 7;
                frames[0]      = 1;   frames[1]      = 2;
            }
            else if (!strcasecmp(preset, "light"))
            {
                strength[0]    = 2; strength[1]    = 4;
                frames[0]      = 2; frames[1]      = 2;
            }
            else if (!strcasecmp(preset, "strong"))
            {
                strength[0]    = 3; strength[1]    = 4;
                range[0]       = 7; range[1]       = 11;
            }
        }
        else
        {
            fprintf(stderr, "Unrecognized nlmeans tune (%s).\n", tune);
            return NULL;
        }

        settings = hb_dict_init();
        hb_dict_set(settings, "y-strength",   hb_value_double(strength[0]));
        hb_dict_set(settings, "y-origin-tune", hb_value_double(origin_tune[0]));
        hb_dict_set(settings, "y-patch-size",  hb_value_int(patch_size[0]));
        hb_dict_set(settings, "y-range",      hb_value_int(range[0]));
        hb_dict_set(settings, "y-frame-count", hb_value_int(frames[0]));
        hb_dict_set(settings, "y-prefilter",  hb_value_int(prefilter[0]));

        hb_dict_set(settings, "cb-strength",   hb_value_double(strength[1]));
        hb_dict_set(settings, "cb-origin-tune", hb_value_double(origin_tune[1]));
        hb_dict_set(settings, "cb-patch-size",  hb_value_int(patch_size[1]));
        hb_dict_set(settings, "cb-range",      hb_value_int(range[1]));
        hb_dict_set(settings, "cb-frame-count", hb_value_int(frames[1]));
        hb_dict_set(settings, "cb-prefilter",  hb_value_int(prefilter[1]));
    }
    else
    {
        settings = hb_parse_filter_settings(preset);
        if (tune != NULL)
        {
            fprintf(stderr, "Custom nlmeans parameters specified; ignoring nlmeans tune (%s).\n", tune);
        }
    }

    return settings;
}