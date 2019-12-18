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
typedef  int /*<<< orphan*/  hb_value_t ;

/* Variables and functions */
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/ * hb_dict_get (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  hb_dict_set (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 char* hb_strdup_printf (char*,int,int) ; 
 char* hb_value_get_string (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hb_value_string (char*) ; 
 int /*<<< orphan*/  sscanf (char const*,char*,int*,int*) ; 
 scalar_t__ strcasecmp (char const*,char*) ; 

__attribute__((used)) static void import_deint_11_0_0(hb_value_t *preset)
{
    hb_value_t *val = hb_dict_get(preset, "PictureDeinterlaceFilter");
    if (val == NULL)
    {
        return;
    }
    const char * deint = hb_value_get_string(val);
    if (deint == NULL)
    {
        // This really shouldn't happen for a valid preset
        return;
    }
    if (strcasecmp(deint, "deinterlace"))
    {
        return;
    }
    val = hb_dict_get(preset, "PictureDeinterlacePreset");
    if (val == NULL)
    {
        hb_dict_set(preset, "PictureDeinterlacePreset",
                    hb_value_string("default"));
        return;
    }
    deint = hb_value_get_string(val);
    if (deint == NULL)
    {
        // This really shouldn't happen for a valid preset
        return;
    }
    if (!strcasecmp(deint, "fast") || !strcasecmp(deint, "slow"))
    {
        // fast and slow -> skip-spatial
        hb_dict_set(preset, "PictureDeinterlacePreset",
                    hb_value_string("skip-spatial"));
        return;
    }
    else if (!strcasecmp(deint, "bob") || !strcasecmp(deint, "default"))
    {
        return;
    }
    else if (strcasecmp(deint, "custom"))
    {
        // not custom -> default
        hb_dict_set(preset, "PictureDeinterlacePreset",
                    hb_value_string("default"));
        return;
    }
    val = hb_dict_get(preset, "PictureDeinterlaceCustom");
    if (val == NULL)
    {
        hb_dict_set(preset, "PictureDeinterlacePreset",
                    hb_value_string("default"));
        return;
    }
    // Translate custom values
    deint = hb_value_get_string(val);
    if (deint == NULL)
    {
        // This really shouldn't happen for a valid preset
        return;
    }
    int bob, spatial, yadif, mode = 3, parity = -1;
    sscanf(deint, "%d:%d", &mode, &parity);
    yadif   = !!(mode & 1);
    spatial = !!(mode & 2);
    bob     = !!(mode & 8);
    mode = yadif + (yadif && spatial) * 2 + bob * 4;
    char * custom = hb_strdup_printf("%d:%d", mode, parity);
    hb_dict_set(preset, "PictureDeinterlaceCustom", hb_value_string(custom));
    free(custom);
}