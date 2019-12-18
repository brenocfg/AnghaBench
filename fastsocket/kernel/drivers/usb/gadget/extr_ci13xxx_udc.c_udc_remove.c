#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;
struct ci13xxx {TYPE_1__ gadget; } ;

/* Variables and functions */
 struct ci13xxx* _udc ; 
 int /*<<< orphan*/  dbg_remove_files (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_unregister (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  err (char*) ; 
 int /*<<< orphan*/  kfree (struct ci13xxx*) ; 

__attribute__((used)) static void udc_remove(void)
{
	struct ci13xxx *udc = _udc;

	if (udc == NULL) {
		err("EINVAL");
		return;
	}

#ifdef CONFIG_USB_GADGET_DEBUG_FILES
	dbg_remove_files(&udc->gadget.dev);
#endif
	device_unregister(&udc->gadget.dev);

	kfree(udc);
	_udc = NULL;
}