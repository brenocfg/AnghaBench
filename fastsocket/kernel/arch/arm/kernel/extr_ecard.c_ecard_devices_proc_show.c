#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct seq_file {int dummy; } ;
struct TYPE_4__ {struct TYPE_4__* next; } ;
typedef  TYPE_1__ ecard_t ;

/* Variables and functions */
 TYPE_1__* cards ; 
 int /*<<< orphan*/  ecard_prints (struct seq_file*,TYPE_1__*) ; 

__attribute__((used)) static int ecard_devices_proc_show(struct seq_file *m, void *v)
{
	ecard_t *ec = cards;

	while (ec) {
		ecard_prints(m, ec);
		ec = ec->next;
	}
	return 0;
}