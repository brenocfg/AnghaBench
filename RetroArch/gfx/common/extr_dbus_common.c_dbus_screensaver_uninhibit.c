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
typedef  int /*<<< orphan*/  DBusMessage ;

/* Variables and functions */
 int /*<<< orphan*/  DBUS_TYPE_INVALID ; 
 int /*<<< orphan*/  DBUS_TYPE_UINT32 ; 
 int /*<<< orphan*/  dbus_connection ; 
 int /*<<< orphan*/  dbus_connection_flush (int /*<<< orphan*/ ) ; 
 scalar_t__ dbus_connection_send (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dbus_message_append_args (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * dbus_message_new_method_call (char*,char*,char*,char*) ; 
 int /*<<< orphan*/  dbus_message_unref (int /*<<< orphan*/ *) ; 
 scalar_t__ dbus_screensaver_cookie ; 

void dbus_screensaver_uninhibit(void)
{
#ifdef HAVE_DBUS
   DBusMessage *msg = NULL;

   if (!dbus_connection)
      return;

   if (dbus_screensaver_cookie == 0)
      return;

   msg = dbus_message_new_method_call("org.freedesktop.ScreenSaver",
         "/org/freedesktop/ScreenSaver",
         "org.freedesktop.ScreenSaver",
         "UnInhibit");
   if (!msg)
       return;

   dbus_message_append_args(msg,
         DBUS_TYPE_UINT32, &dbus_screensaver_cookie,
         DBUS_TYPE_INVALID);

   if (dbus_connection_send(dbus_connection, msg, NULL))
      dbus_connection_flush(dbus_connection);
   dbus_message_unref(msg);

   dbus_screensaver_cookie = 0;
#endif
}