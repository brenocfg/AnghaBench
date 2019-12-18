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
 int S_IFREG ; 
 int S_IRUGO ; 
 int S_IWUSR ; 
 int /*<<< orphan*/ * proc_create (char*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * tape_proc_devices ; 
 int /*<<< orphan*/  tape_proc_ops ; 

void
tape_proc_init(void)
{
	tape_proc_devices =
		proc_create("tapedevices", S_IFREG | S_IRUGO | S_IWUSR, NULL,
			    &tape_proc_ops);
	if (tape_proc_devices == NULL) {
		return;
	}
}