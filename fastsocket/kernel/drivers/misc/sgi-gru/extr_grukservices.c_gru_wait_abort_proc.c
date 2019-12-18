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
 int /*<<< orphan*/  gru_abort (int,void*,char*) ; 
 int gru_wait_proc (void*) ; 

void gru_wait_abort_proc(void *cb)
{
	int ret;

	ret = gru_wait_proc(cb);
	if (ret)
		gru_abort(ret, cb, "gru_wait_abort");
}