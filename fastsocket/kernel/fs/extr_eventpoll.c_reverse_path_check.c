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
struct tfile_check {int count; struct tfile_check* next; TYPE_1__** tfile_arr; } ;
struct TYPE_2__ {int /*<<< orphan*/  file; } ;

/* Variables and functions */
 int /*<<< orphan*/  EP_MAX_NESTS ; 
 struct tfile_check base_tfile_check ; 
 int /*<<< orphan*/  current ; 
 int ep_call_nested (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  path_count_init () ; 
 int /*<<< orphan*/  poll_loop_ncalls ; 
 int /*<<< orphan*/  reverse_path_check_proc ; 

__attribute__((used)) static int reverse_path_check(void)
{
	int length = 0;
	int error = 0;
	int i;
	struct tfile_check *tfile_check_iter = &base_tfile_check;

	/* let's call this for all tfiles */
	while (tfile_check_iter) {
		for (i = 0; i < tfile_check_iter->count; i++) {
			length++;
			path_count_init();
			error = ep_call_nested(&poll_loop_ncalls, EP_MAX_NESTS,
					reverse_path_check_proc, tfile_check_iter->tfile_arr[i]->file,
					tfile_check_iter->tfile_arr[i]->file, current);
			if (error)
				return error;
		}
		tfile_check_iter = tfile_check_iter->next;
	}
	return error;
}