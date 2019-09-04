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
struct timespec {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;
typedef  int /*<<< orphan*/  mqd_t ;

/* Variables and functions */
 int /*<<< orphan*/  SYS_mq_timedreceive ; 
 int /*<<< orphan*/  syscall_cp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,size_t,unsigned int*,struct timespec const*) ; 

ssize_t mq_timedreceive(mqd_t mqd, char *restrict msg, size_t len, unsigned *restrict prio, const struct timespec *restrict at)
{
	return syscall_cp(SYS_mq_timedreceive, mqd, msg, len, prio, at);
}