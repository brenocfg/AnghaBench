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
typedef  int /*<<< orphan*/  GtkBuilder ;
typedef  int /*<<< orphan*/  GObject ;
typedef  int GConnectFlags ;
typedef  int /*<<< orphan*/  GCallback ;

/* Variables and functions */
 int G_CONNECT_AFTER ; 
 int /*<<< orphan*/  g_debug (char*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  g_message (char*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  g_return_if_fail (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_signal_connect (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_signal_connect_after (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_signal_connect_object (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  self_symbol_lookup (int /*<<< orphan*/  const*) ; 

__attribute__((used)) static void
MyConnect(
    GtkBuilder *builder,
    GObject *object,
    const gchar *signal_name,
    const gchar *handler_name,
    GObject *connect_object,
    GConnectFlags flags,
    gpointer user_data)
{
    GCallback callback;

    g_return_if_fail(object != NULL);
    g_return_if_fail(handler_name != NULL);
    g_return_if_fail(signal_name != NULL);

    //const gchar *name = ghb_get_setting_key((GtkWidget*)object);
    //g_message("\n\nname %s", name);
    g_debug("handler_name %s", handler_name);
    g_debug("signal_name %s", signal_name);
    callback = self_symbol_lookup(handler_name);
    if (!callback)
    {
        g_message("Signal handler (%s) not found", handler_name);
        return;
    }
    if (connect_object)
    {
        g_signal_connect_object(object, signal_name, callback, connect_object, flags);
    }
    else
    {
        if (flags & G_CONNECT_AFTER)
        {
            g_signal_connect_after( object, signal_name, callback, user_data);
        }
        else
        {
            g_signal_connect(object, signal_name, callback, user_data);
        }
    }
}