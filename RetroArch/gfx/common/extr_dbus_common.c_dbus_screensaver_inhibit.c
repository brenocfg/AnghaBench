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
 int /*<<< orphan*/  DBUS_TYPE_STRING ; 
 int /*<<< orphan*/  DBUS_TYPE_UINT32 ; 
 int /*<<< orphan*/  RARCH_ERR (char*) ; 
 int /*<<< orphan*/  RARCH_LOG (char*) ; 
 int /*<<< orphan*/  dbus_connection ; 
 int /*<<< orphan*/ * dbus_connection_send_with_reply_and_block (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dbus_message_append_args (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const**,int /*<<< orphan*/ ,char const**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dbus_message_get_args (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * dbus_message_new_method_call (char*,char*,char*,char*) ; 
 int /*<<< orphan*/  dbus_message_unref (int /*<<< orphan*/ *) ; 
 scalar_t__ dbus_screensaver_cookie ; 

bool dbus_screensaver_inhibit(void)
{
   bool ret           = false;
#ifdef HAVE_DBUS
   const char *app    = "RetroArch";
   const char *reason = "Playing a game";
   DBusMessage   *msg = NULL;
   DBusMessage *reply = NULL;

   if (!dbus_connection)
      return false; /* DBus connection was not obtained */

   if (dbus_screensaver_cookie > 0)
      return true; /* Already inhibited */

   msg = dbus_message_new_method_call("org.freedesktop.ScreenSaver",
         "/org/freedesktop/ScreenSaver",
         "org.freedesktop.ScreenSaver",
         "Inhibit");

   if (!msg)
      return false;

   if (!dbus_message_append_args(msg,
            DBUS_TYPE_STRING, &app,
            DBUS_TYPE_STRING, &reason,
            DBUS_TYPE_INVALID))
   {
      dbus_message_unref(msg);
      return false;
   }

   reply = dbus_connection_send_with_reply_and_block(dbus_connection,
         msg, 300, NULL);

   if (reply != NULL)
   {
      if (!dbus_message_get_args(reply, NULL,
               DBUS_TYPE_UINT32, &dbus_screensaver_cookie,
               DBUS_TYPE_INVALID))
         dbus_screensaver_cookie = 0;
      else
         ret = true;

      dbus_message_unref(reply);
   }

   dbus_message_unref(msg);

   if (dbus_screensaver_cookie == 0)
   {
      RARCH_ERR("[DBus]: Failed to suspend screensaver via DBus.\n");
   }
   else
   {
      RARCH_LOG("[DBus]: Suspended screensaver via DBus.\n");
   }

#endif

   return ret;
}