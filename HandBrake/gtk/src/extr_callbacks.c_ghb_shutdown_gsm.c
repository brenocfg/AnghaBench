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
typedef  int /*<<< orphan*/  GVariant ;
typedef  int /*<<< orphan*/  GError ;
typedef  int /*<<< orphan*/  GDBusProxy ;

/* Variables and functions */
 int /*<<< orphan*/  GPM_DBUS_SM_INTERFACE ; 
 int /*<<< orphan*/  GPM_DBUS_SM_PATH ; 
 int /*<<< orphan*/  GPM_DBUS_SM_SERVICE ; 
 int /*<<< orphan*/  G_DBUS_CALL_FLAGS_NONE ; 
 int /*<<< orphan*/  G_OBJECT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * g_dbus_proxy_call_sync (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  g_debug (char*) ; 
 int /*<<< orphan*/  g_error_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  g_object_unref (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_variant_unref (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ghb_get_session_dbus_proxy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ghb_shutdown_gpm () ; 

__attribute__((used)) static void
ghb_shutdown_gsm()
{
#if !defined(_WIN32)
    GDBusProxy  *proxy;
    GError *error = NULL;
    GVariant *res;


    g_debug("ghb_shutdown_gpm()");
    proxy = ghb_get_session_dbus_proxy(GPM_DBUS_SM_SERVICE,
                            GPM_DBUS_SM_PATH, GPM_DBUS_SM_INTERFACE);
    if (proxy == NULL)
        return;

    res = g_dbus_proxy_call_sync(proxy, "Shutdown", NULL,
                                 G_DBUS_CALL_FLAGS_NONE, -1, NULL, &error);
    g_object_unref(G_OBJECT(proxy));
    if (!res)
    {
        if (error != NULL)
        {
            g_error_free(error);
        }
        // Try the gpm version
        ghb_shutdown_gpm();
    }
    else
    {
        g_variant_unref(res);
    }
#endif
}