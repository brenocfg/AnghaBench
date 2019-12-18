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
typedef  int /*<<< orphan*/  GhbValue ;

/* Variables and functions */
 int /*<<< orphan*/  ghb_dict_copy (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ghb_dict_get (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/ * ghb_resource_get (char*) ; 

void
ghb_settings_init(GhbValue *settings, const char *name)
{
    GhbValue    *internal;

    GhbValue *internalDict = ghb_resource_get("internal-defaults");
    // Setting a ui widget will cause the corresponding setting
    // to be set, but it also triggers a callback that can
    // have the side effect of using other settings values
    // that have not yet been set.  So set *all* settings first
    // then update the ui.
    internal = ghb_dict_get(internalDict, name);
    ghb_dict_copy(settings, internal);
}