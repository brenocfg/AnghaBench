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
struct TYPE_2__ {int /*<<< orphan*/  fu_list; } ;
struct file {TYPE_1__ f_u; } ;

/* Variables and functions */
 int /*<<< orphan*/  file_list_lock () ; 
 int /*<<< orphan*/  file_list_unlock () ; 
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 

void file_kill(struct file *file)
{
	if (!list_empty(&file->f_u.fu_list)) {
		file_list_lock();
		list_del_init(&file->f_u.fu_list);
		file_list_unlock();
	}
}