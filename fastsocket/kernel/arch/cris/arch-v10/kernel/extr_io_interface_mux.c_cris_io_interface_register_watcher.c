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
struct watcher {void (* notify ) (unsigned int const,unsigned int const,unsigned char const,unsigned char const) ;struct watcher* next; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  cris_io_interface_init () ; 
 scalar_t__ gpio_in_pins ; 
 scalar_t__ gpio_out_pins ; 
 scalar_t__ gpio_pa_pins ; 
 scalar_t__ gpio_pb_pins ; 
 struct watcher* kmalloc (int,int /*<<< orphan*/ ) ; 
 void stub1 (unsigned int const,unsigned int const,unsigned char const,unsigned char const) ; 
 struct watcher* watchers ; 

int cris_io_interface_register_watcher(void (*notify)(const unsigned int gpio_in_available,
                                                      const unsigned int gpio_out_available,
                                                      const unsigned char pa_available,
                                                      const unsigned char pb_available))
{
	struct watcher *w;

	(void)cris_io_interface_init();

	if (NULL == notify) {
		return -EINVAL;
	}
	w = kmalloc(sizeof(*w), GFP_KERNEL);
	if (!w) {
		return -ENOMEM;
	}
	w->notify = notify;
	w->next = watchers;
	watchers = w;

	w->notify((const unsigned int)gpio_in_pins,
		  (const unsigned int)gpio_out_pins,
		  (const unsigned char)gpio_pa_pins,
		  (const unsigned char)gpio_pb_pins);

	return 0;
}