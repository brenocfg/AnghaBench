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
struct thread_info {int /*<<< orphan*/ * reg_window; int /*<<< orphan*/ * rwbuf_stkptrs; } ;
struct reg_window {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static inline void shift_window_buffer(int first_win, int last_win,
				       struct thread_info *t)
{
	int i;

	for (i = first_win; i < last_win; i++) {
		t->rwbuf_stkptrs[i] = t->rwbuf_stkptrs[i+1];
		memcpy(&t->reg_window[i], &t->reg_window[i+1],
		       sizeof(struct reg_window));
	}
}