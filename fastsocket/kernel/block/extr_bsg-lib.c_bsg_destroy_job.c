#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {struct bsg_job* sg_list; } ;
struct TYPE_3__ {struct bsg_job* sg_list; } ;
struct bsg_job {TYPE_2__ reply_payload; TYPE_1__ request_payload; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct bsg_job*) ; 
 int /*<<< orphan*/  put_device (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void bsg_destroy_job(struct bsg_job *job)
{
	put_device(job->dev);	/* release reference for the request */

	kfree(job->request_payload.sg_list);
	kfree(job->reply_payload.sg_list);
	kfree(job);
}