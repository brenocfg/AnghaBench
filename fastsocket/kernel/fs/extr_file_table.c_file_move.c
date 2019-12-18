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
struct list_head {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  fu_list; } ;
struct file {TYPE_1__ f_u; } ;

/* Variables and functions */
 int /*<<< orphan*/  file_list_lock () ; 
 int /*<<< orphan*/  file_list_unlock () ; 
 int /*<<< orphan*/  list_move (int /*<<< orphan*/ *,struct list_head*) ; 

void file_move(struct file *file, struct list_head *list)
{
	if (!list)
		return;
	file_list_lock();
	list_move(&file->f_u.fu_list, list);
	file_list_unlock();
}