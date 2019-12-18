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
 int /*<<< orphan*/  divas_fops ; 
 int /*<<< orphan*/  divas_proc_entry ; 
 int /*<<< orphan*/  divas_proc_name ; 
 int /*<<< orphan*/  proc_create (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  proc_net_eicon ; 

int create_divas_proc(void)
{
	divas_proc_entry = proc_create(divas_proc_name, S_IFREG | S_IRUGO,
					proc_net_eicon, &divas_fops);
	if (!divas_proc_entry)
		return (0);

	return (1);
}