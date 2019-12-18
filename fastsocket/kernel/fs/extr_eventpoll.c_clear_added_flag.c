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
struct tfile_check {int count; TYPE_1__** tfile_arr; } ;
struct TYPE_2__ {scalar_t__ added; } ;

/* Variables and functions */

__attribute__((used)) static void clear_added_flag(struct tfile_check *tfile_check_iter)
{
	int i;

	for (i = 0; i < tfile_check_iter->count; i++)
		tfile_check_iter->tfile_arr[i]->added = 0;
}