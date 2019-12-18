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
struct slip_pre_exec_data {scalar_t__ stdin; scalar_t__ stdout; scalar_t__ close_me; } ;

/* Variables and functions */
 int /*<<< orphan*/  close (scalar_t__) ; 
 int /*<<< orphan*/  dup2 (scalar_t__,int) ; 

__attribute__((used)) static void slip_pre_exec(void *arg)
{
	struct slip_pre_exec_data *data = arg;

	if (data->stdin >= 0)
		dup2(data->stdin, 0);
	dup2(data->stdout, 1);
	if (data->close_me >= 0)
		close(data->close_me);
}