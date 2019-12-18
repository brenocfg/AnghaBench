#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct parport {int dummy; } ;
struct i2c_par {struct i2c_par* next; TYPE_1__* pdev; int /*<<< orphan*/  adapter; } ;
struct TYPE_6__ {scalar_t__ val; } ;
struct TYPE_7__ {TYPE_3__ init; } ;
struct TYPE_5__ {struct parport* port; } ;

/* Variables and functions */
 struct i2c_par* adapter_list ; 
 TYPE_4__* adapter_parm ; 
 int /*<<< orphan*/  i2c_del_adapter (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct i2c_par*) ; 
 int /*<<< orphan*/  line_set (struct parport*,int /*<<< orphan*/ ,TYPE_3__*) ; 
 int /*<<< orphan*/  parport_release (TYPE_1__*) ; 
 int /*<<< orphan*/  parport_unregister_device (TYPE_1__*) ; 
 size_t type ; 

__attribute__((used)) static void i2c_parport_detach (struct parport *port)
{
	struct i2c_par *adapter, *prev;

	/* Walk the list */
	for (prev = NULL, adapter = adapter_list; adapter;
	     prev = adapter, adapter = adapter->next) {
		if (adapter->pdev->port == port) {
			i2c_del_adapter(&adapter->adapter);

			/* Un-init if needed (power off...) */
			if (adapter_parm[type].init.val)
				line_set(port, 0, &adapter_parm[type].init);
				
			parport_release(adapter->pdev);
			parport_unregister_device(adapter->pdev);
			if (prev)
				prev->next = adapter->next;
			else
				adapter_list = adapter->next;
			kfree(adapter);
			return;
		}
	}
}