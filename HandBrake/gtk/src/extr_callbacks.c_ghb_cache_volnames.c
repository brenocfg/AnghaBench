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
typedef  int /*<<< orphan*/  signal_user_data_t ;
typedef  int /*<<< orphan*/ * gpointer ;
typedef  int /*<<< orphan*/  gchar ;
struct TYPE_4__ {struct TYPE_4__* next; int /*<<< orphan*/  data; } ;
typedef  int /*<<< orphan*/  GSourceFunc ;
typedef  TYPE_1__ GList ;

/* Variables and functions */
 TYPE_1__* dvd_device_list () ; 
 int /*<<< orphan*/  free_drive (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_debug (char*) ; 
 int /*<<< orphan*/  g_drive_has_media (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  g_hash_table_insert (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  g_hash_table_remove_all (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_idle_add (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  g_list_free (TYPE_1__*) ; 
 int /*<<< orphan*/  g_mutex_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_mutex_unlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_object_unref (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * get_direct_dvd_volume_name (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * get_dvd_device_name (int /*<<< orphan*/ ) ; 
 scalar_t__ ghb_file_menu_add_dvd ; 
 int /*<<< orphan*/  volname_hash ; 
 int /*<<< orphan*/  volname_mutex ; 

gpointer
ghb_cache_volnames(signal_user_data_t *ud)
{
    GList *link, *drives;

    g_debug("ghb_cache_volnames()");
    link = drives = dvd_device_list();
    if (drives == NULL)
        return NULL;

    g_mutex_lock(volname_mutex);
    g_hash_table_remove_all(volname_hash);
    while (link != NULL)
    {
        gchar *name, *drive;

#if !defined(_WIN32)
        if (!g_drive_has_media (link->data))
        {
            g_object_unref(link->data);
            link = link->next;
            continue;
        }
#endif
        drive = get_dvd_device_name(link->data);
        name = get_direct_dvd_volume_name(drive);

        if (drive != NULL && name != NULL)
        {
            g_hash_table_insert(volname_hash, drive, name);
        }
        else
        {
            if (drive != NULL)
                g_free(drive);
            if (name != NULL)
                g_free(name);
        }

        free_drive(link->data);
        link = link->next;
    }
    g_mutex_unlock(volname_mutex);

    g_list_free(drives);

    g_idle_add((GSourceFunc)ghb_file_menu_add_dvd, ud);

    return NULL;
}