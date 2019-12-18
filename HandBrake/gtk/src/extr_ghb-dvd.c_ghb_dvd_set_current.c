#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/ * current_dvd_device; } ;
typedef  TYPE_1__ signal_user_data_t ;
typedef  scalar_t__ guint ;
typedef  int /*<<< orphan*/  gchar ;
typedef  int /*<<< orphan*/  GFileInfo ;
typedef  int /*<<< orphan*/  GFile ;

/* Variables and functions */
 scalar_t__ DRIVE_CDROM ; 
 int /*<<< orphan*/  G_FILE_ATTRIBUTE_STANDARD_TYPE ; 
 int /*<<< orphan*/  G_FILE_QUERY_INFO_NONE ; 
 scalar_t__ G_FILE_TYPE_SPECIAL ; 
 scalar_t__ GetDriveType (int /*<<< orphan*/ *) ; 
 scalar_t__ g_file_info_get_file_type (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * g_file_new_for_path (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * g_file_query_info (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  g_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  g_object_unref (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * g_strdup (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  g_strlcpy (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/ * ghb_resolve_symlink (int /*<<< orphan*/  const*) ; 

void
ghb_dvd_set_current(const gchar *name, signal_user_data_t *ud)
{
#if !defined(_WIN32)
    GFile *gfile;
    GFileInfo *info;
    gchar *resolved = ghb_resolve_symlink(name);

    if (ud->current_dvd_device != NULL)
    {
        g_free(ud->current_dvd_device);
        ud->current_dvd_device = NULL;
    }
    gfile = g_file_new_for_path(resolved);
    info = g_file_query_info(gfile,
        G_FILE_ATTRIBUTE_STANDARD_TYPE,
        G_FILE_QUERY_INFO_NONE, NULL, NULL);
    if (info != NULL)
    {
        if (g_file_info_get_file_type(info) == G_FILE_TYPE_SPECIAL)
        {
            // I could go through the trouble to scan the connected drives and
            // verify that this device is connected and is a DVD.  But I don't
            // think its necessary.
            ud->current_dvd_device = resolved;
        }
        else
        {
            g_free(resolved);
        }
        g_object_unref(info);
    }
    else
    {
        g_free(resolved);
    }
    g_object_unref(gfile);
#else
    gchar drive[4];
    guint dtype;

    if (ud->current_dvd_device != NULL)
    {
        g_free(ud->current_dvd_device);
        ud->current_dvd_device = NULL;
    }
    g_strlcpy(drive, name, 4);
    dtype = GetDriveType(drive);
    if (dtype == DRIVE_CDROM)
    {
        ud->current_dvd_device = g_strdup(name);
    }
#endif
}