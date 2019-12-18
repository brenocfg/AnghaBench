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
typedef  int /*<<< orphan*/  GhbValue ;

/* Variables and functions */
 int /*<<< orphan*/  G_FILE_TEST_IS_REGULAR ; 
 scalar_t__ g_file_test (int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * ghb_json_parse_file (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/ * hb_plist_parse_file (int /*<<< orphan*/  const*) ; 

GhbValue*
ghb_read_settings_file(const gchar *path)
{
    GhbValue *gval = NULL;

    if (g_file_test(path, G_FILE_TEST_IS_REGULAR))
    {
        gval = ghb_json_parse_file(path);
        if (gval == NULL)
            gval = hb_plist_parse_file(path);
    }
    return gval;
}