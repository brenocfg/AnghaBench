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
typedef  int /*<<< orphan*/  gchar ;
struct TYPE_4__ {int /*<<< orphan*/  const* message; } ;
typedef  TYPE_1__ GError ;
typedef  int /*<<< orphan*/  GDBusProxy ;
typedef  int /*<<< orphan*/  GDBusConnection ;

/* Variables and functions */
 int /*<<< orphan*/  G_BUS_TYPE_SESSION ; 
 int /*<<< orphan*/  G_DBUS_PROXY_FLAGS_NONE ; 
 int /*<<< orphan*/ * g_bus_get_sync (int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_1__**) ; 
 int /*<<< orphan*/ * g_dbus_proxy_new_sync (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  g_debug (char*) ; 
 int /*<<< orphan*/  g_error_free (TYPE_1__*) ; 
 int /*<<< orphan*/  g_object_unref (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  g_warning (char*,int /*<<< orphan*/  const*) ; 

__attribute__((used)) static GDBusProxy *
ghb_get_session_dbus_proxy(const gchar *name, const gchar *path, const gchar *interface)
{
    GDBusConnection *conn;
    GDBusProxy *proxy;
    GError *error = NULL;

    g_debug("ghb_get_session_dbus_proxy()");
    conn = g_bus_get_sync(G_BUS_TYPE_SESSION, NULL, &error);
    if (conn == NULL)
    {
        if (error != NULL)
        {
            g_warning("DBUS cannot connect: %s", error->message);
            g_error_free(error);
        }
        return NULL;
    }

    proxy = g_dbus_proxy_new_sync(conn, G_DBUS_PROXY_FLAGS_NONE, NULL,
                                  name, path, interface, NULL, NULL);
    if (proxy == NULL)
        g_warning("Could not get DBUS proxy: %s", name);

    g_object_unref(conn);
    return proxy;
}