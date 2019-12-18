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
struct proc_entry {int /*<<< orphan*/  entry; int /*<<< orphan*/  fops; int /*<<< orphan*/  mode; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  proc_create (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  proc_gru ; 

__attribute__((used)) static int create_proc_file(struct proc_entry *p)
{
	p->entry = proc_create(p->name, p->mode, proc_gru, p->fops);
	if (!p->entry)
		return -1;
	return 0;
}