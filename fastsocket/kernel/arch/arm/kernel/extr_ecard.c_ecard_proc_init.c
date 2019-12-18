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
 int /*<<< orphan*/  bus_ecard_proc_fops ; 
 int /*<<< orphan*/  proc_bus_ecard_dir ; 
 int /*<<< orphan*/  proc_create (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  proc_mkdir (char*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ecard_proc_init(void)
{
	proc_bus_ecard_dir = proc_mkdir("bus/ecard", NULL);
	proc_create("devices", 0, proc_bus_ecard_dir, &bus_ecard_proc_fops);
}