#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int echo; int /*<<< orphan*/ * buf; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 TYPE_1__* TIPC_LOG ; 
 int TIPC_PB_MIN_SIZE ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  print_lock ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tipc_printbuf_init (TYPE_1__*,int /*<<< orphan*/ ,int) ; 

int tipc_log_resize(int log_size)
{
	int res = 0;

	spin_lock_bh(&print_lock);
	if (TIPC_LOG->buf) {
		kfree(TIPC_LOG->buf);
		TIPC_LOG->buf = NULL;
	}
	if (log_size) {
		if (log_size < TIPC_PB_MIN_SIZE)
			log_size = TIPC_PB_MIN_SIZE;
		res = TIPC_LOG->echo;
		tipc_printbuf_init(TIPC_LOG, kmalloc(log_size, GFP_ATOMIC),
				   log_size);
		TIPC_LOG->echo = res;
		res = !TIPC_LOG->buf;
	}
	spin_unlock_bh(&print_lock);

	return res;
}