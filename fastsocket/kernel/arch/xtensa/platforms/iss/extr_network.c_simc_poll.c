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
struct timeval {int /*<<< orphan*/  tv_usec; int /*<<< orphan*/  tv_sec; } ;

/* Variables and functions */
 int /*<<< orphan*/  SYS_select_one ; 
 int /*<<< orphan*/  XTISS_SELECT_ONE_READ ; 
 int __simc (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int inline simc_poll(int fd)
{
	struct timeval tv = { .tv_sec = 0, .tv_usec = 0 };

	return __simc(SYS_select_one, fd, XTISS_SELECT_ONE_READ, (int)&tv,0,0);
}