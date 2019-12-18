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
struct slirp_pre_exec_data {int stdin; int stdout; } ;

/* Variables and functions */
 int /*<<< orphan*/  dup2 (int,int) ; 

__attribute__((used)) static void slirp_pre_exec(void *arg)
{
	struct slirp_pre_exec_data *data = arg;

	if (data->stdin != -1)
		dup2(data->stdin, 0);
	if (data->stdout != -1)
		dup2(data->stdout, 1);
}