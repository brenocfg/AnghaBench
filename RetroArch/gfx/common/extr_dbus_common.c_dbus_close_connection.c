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

/* Variables and functions */
 int /*<<< orphan*/ * dbus_connection ; 
 int /*<<< orphan*/  dbus_connection_close (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dbus_connection_unref (int /*<<< orphan*/ *) ; 

void dbus_close_connection(void)
{
#ifdef HAVE_DBUS
   if (!dbus_connection)
      return;

   dbus_connection_close(dbus_connection);
   dbus_connection_unref(dbus_connection);
   dbus_connection = NULL;
#endif
}