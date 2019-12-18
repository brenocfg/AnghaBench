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
typedef  int /*<<< orphan*/  gpointer ;
typedef  int /*<<< orphan*/  gchar ;

/* Variables and functions */
 int /*<<< orphan*/  camel_convert (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  g_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  g_hash_table_lookup (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  g_mutex_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_mutex_unlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * g_strdup (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * g_strdup_printf (char*,int /*<<< orphan*/ *,...) ; 
 int /*<<< orphan*/ * get_dvd_device_name (int /*<<< orphan*/ ) ; 
 scalar_t__ uppers_and_unders (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  volname_hash ; 
 int /*<<< orphan*/  volname_mutex ; 

__attribute__((used)) static gchar*
get_dvd_volume_name(gpointer gd)
{
    gchar *label = NULL;
    gchar *result;
    gchar *drive;

    drive = get_dvd_device_name(gd);
    g_mutex_lock(volname_mutex);
    label = g_strdup(g_hash_table_lookup(volname_hash, drive));
    g_mutex_unlock(volname_mutex);
    if (label != NULL)
    {
        if (uppers_and_unders(label))
        {
            camel_convert(label);
        }
#if defined(_WIN32)
        result = g_strdup_printf("%s (%s)", label, drive);
#else
        result = g_strdup_printf("%s - %s", drive, label);
#endif
        g_free(label);
    }
    else
    {
        result = g_strdup_printf("%s", drive);
    }
    g_free(drive);
    return result;
}