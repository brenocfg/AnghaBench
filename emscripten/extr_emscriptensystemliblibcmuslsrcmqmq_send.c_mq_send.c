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
typedef  int /*<<< orphan*/  mqd_t ;

/* Variables and functions */
 int mq_timedsend (int /*<<< orphan*/ ,char const*,size_t,unsigned int,int /*<<< orphan*/ ) ; 

int mq_send(mqd_t mqd, const char *msg, size_t len, unsigned prio)
{
	return mq_timedsend(mqd, msg, len, prio, 0);
}