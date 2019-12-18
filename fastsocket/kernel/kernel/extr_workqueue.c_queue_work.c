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
struct workqueue_struct {int dummy; } ;
struct work_struct {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  get_cpu () ; 
 int /*<<< orphan*/  put_cpu () ; 
 int queue_work_on (int /*<<< orphan*/ ,struct workqueue_struct*,struct work_struct*) ; 

int queue_work(struct workqueue_struct *wq, struct work_struct *work)
{
	int ret;

	ret = queue_work_on(get_cpu(), wq, work);
	put_cpu();

	return ret;
}