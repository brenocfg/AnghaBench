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
struct uvesafb_ktask {struct completion* done; } ;
struct completion {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  memset (struct uvesafb_ktask*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void uvesafb_reset(struct uvesafb_ktask *task)
{
	struct completion *cpl = task->done;

	memset(task, 0, sizeof(*task));
	task->done = cpl;
}