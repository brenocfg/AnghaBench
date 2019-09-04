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
struct mq_attr {int dummy; } ;
typedef  int /*<<< orphan*/  mqd_t ;

/* Variables and functions */
 int mq_setattr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct mq_attr*) ; 

int mq_getattr(mqd_t mqd, struct mq_attr *attr)
{
	return mq_setattr(mqd, 0, attr);
}