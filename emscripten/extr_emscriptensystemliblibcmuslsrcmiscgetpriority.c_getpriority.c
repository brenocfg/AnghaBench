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
typedef  int /*<<< orphan*/  id_t ;

/* Variables and functions */
 int /*<<< orphan*/  SYS_getpriority ; 
 int syscall (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

int getpriority(int which, id_t who)
{
	int ret = syscall(SYS_getpriority, which, who);
	if (ret < 0) return ret;
	return 20-ret;
}