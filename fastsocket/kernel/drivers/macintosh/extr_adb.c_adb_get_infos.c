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
struct TYPE_2__ {int original_address; int handler_id; } ;

/* Variables and functions */
 TYPE_1__* adb_handler ; 
 int /*<<< orphan*/  adb_handler_mutex ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

int
adb_get_infos(int address, int *original_address, int *handler_id)
{
	mutex_lock(&adb_handler_mutex);
	*original_address = adb_handler[address].original_address;
	*handler_id = adb_handler[address].handler_id;
	mutex_unlock(&adb_handler_mutex);

	return (*original_address != 0);
}