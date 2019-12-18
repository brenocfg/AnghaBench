#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  globals; } ;
typedef  TYPE_1__ signal_user_data_t ;
typedef  int /*<<< orphan*/  gchar ;
typedef  int /*<<< orphan*/  gboolean ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  g_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * g_strdup (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ghb_dict_get_string (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ghb_do_scan (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

gboolean
ghb_idle_scan(signal_user_data_t *ud)
{
    gchar *path;
    // ghb_do_scan replaces "scan_source" key in dict, so we must
    // make a copy of the string.
    path = g_strdup(ghb_dict_get_string(ud->globals, "scan_source"));
    ghb_do_scan(ud, path, 0, TRUE);
    g_free(path);
    return FALSE;
}