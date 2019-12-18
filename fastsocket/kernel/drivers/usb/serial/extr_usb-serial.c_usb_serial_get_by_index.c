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
struct usb_serial {int /*<<< orphan*/  kref; int /*<<< orphan*/  disc_mutex; scalar_t__ disconnected; } ;

/* Variables and functions */
 int /*<<< orphan*/  kref_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct usb_serial** serial_table ; 
 int /*<<< orphan*/  table_lock ; 

struct usb_serial *usb_serial_get_by_index(unsigned index)
{
	struct usb_serial *serial;

	mutex_lock(&table_lock);
	serial = serial_table[index];

	if (serial) {
		mutex_lock(&serial->disc_mutex);
		if (serial->disconnected) {
			mutex_unlock(&serial->disc_mutex);
			serial = NULL;
		} else {
			kref_get(&serial->kref);
		}
	}
	mutex_unlock(&table_lock);
	return serial;
}