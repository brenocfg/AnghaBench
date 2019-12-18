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
struct watcher {struct watcher* next; int /*<<< orphan*/  (* notify ) (unsigned int const,unsigned int const,unsigned char const,unsigned char const) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  DBG (int /*<<< orphan*/ ) ; 
 scalar_t__ gpio_in_pins ; 
 scalar_t__ gpio_out_pins ; 
 scalar_t__ gpio_pa_pins ; 
 scalar_t__ gpio_pb_pins ; 
 int /*<<< orphan*/  printk (char*) ; 
 int /*<<< orphan*/  stub1 (unsigned int const,unsigned int const,unsigned char const,unsigned char const) ; 
 struct watcher* watchers ; 

__attribute__((used)) static void notify_watchers(void)
{
	struct watcher *w = watchers;

	DBG(printk("io_interface_mux: notifying watchers\n"));

	while (NULL != w) {
		w->notify((const unsigned int)gpio_in_pins,
			  (const unsigned int)gpio_out_pins,
			  (const unsigned char)gpio_pa_pins,
			  (const unsigned char)gpio_pb_pins);
		w = w->next;
	}
}