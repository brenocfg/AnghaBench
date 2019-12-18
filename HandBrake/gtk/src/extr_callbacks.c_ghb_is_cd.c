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
typedef  int gint ;
typedef  int /*<<< orphan*/  gchar ;
typedef  int /*<<< orphan*/  gboolean ;
typedef  int /*<<< orphan*/  GUdevDevice ;
typedef  int /*<<< orphan*/  GDrive ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  G_VOLUME_IDENTIFIER_KIND_UNIX_DEVICE ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/ * g_drive_get_identifier (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  g_message (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  g_object_unref (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * g_udev_client_query_by_device_file (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int g_udev_device_get_property_as_int (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/ * udev_ctx ; 

gboolean
ghb_is_cd(GDrive *gd)
{
#if defined(__linux__) && defined(_HAVE_GUDEV)
    gchar *device;
    GUdevDevice *udd;

    if (udev_ctx == NULL)
        return FALSE;

    device = g_drive_get_identifier(gd, G_VOLUME_IDENTIFIER_KIND_UNIX_DEVICE);
    if (device == NULL)
        return FALSE;

    udd = g_udev_client_query_by_device_file(udev_ctx, device);
    if (udd == NULL)
    {
        g_message("udev: Failed to lookup device %s", device);
        g_free(device);
        return FALSE;
    }
    g_free(device);

    gint val;
    val = g_udev_device_get_property_as_int(udd, "ID_CDROM_DVD");
    g_object_unref(udd);
    if (val == 1)
        return TRUE;

    return FALSE;
#else
    return FALSE;
#endif
}