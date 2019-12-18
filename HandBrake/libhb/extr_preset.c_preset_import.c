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
 scalar_t__ cmpVersion (int,int,int,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hb_dict_get (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  hb_preset_template ; 
 int /*<<< orphan*/  hb_value_get_bool (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  import_0_0_0 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  import_10_0_0 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  import_11_0_0 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  import_11_1_0 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  import_12_0_0 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  import_20_0_0 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  import_25_0_0 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  import_35_0_0 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  preset_clean (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int preset_import(hb_value_t *preset, int major, int minor, int micro)
{
    int result = 0;

    if (!hb_value_get_bool(hb_dict_get(preset, "Folder")))
    {
        if (cmpVersion(major, minor, micro, 0, 0, 0) <= 0)
        {
            // Convert legacy presets (before versioning introduced)
            import_0_0_0(preset);
            result = 1;
        }
        else if (cmpVersion(major, minor, micro, 10, 0, 0) <= 0)
        {
            import_10_0_0(preset);
            result = 1;
        }
        else if (cmpVersion(major, minor, micro, 11, 0, 0) <= 0)
        {
            import_11_0_0(preset);
            result = 1;
        }
        else if (cmpVersion(major, minor, micro, 11, 1, 0) <= 0)
        {
            import_11_1_0(preset);
            result = 1;
        }
        else if (cmpVersion(major, minor, micro, 12, 0, 0) <= 0)
        {
            import_12_0_0(preset);
            result = 1;
        }
        else if (cmpVersion(major, minor, micro, 20, 0, 0) <= 0)
        {
            import_20_0_0(preset);
            result = 1;
        }
        else if (cmpVersion(major, minor, micro, 25, 0, 0) <= 0)
        {
            import_25_0_0(preset);
            result = 1;
        }
        else if (cmpVersion(major, minor, micro, 35, 0, 0) <= 0)
        {
            import_35_0_0(preset);
            result = 1;
        }
        preset_clean(preset, hb_preset_template);
    }
    return result;
}