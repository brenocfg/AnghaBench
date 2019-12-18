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
struct TYPE_3__ {int /*<<< orphan*/  mutex; } ;
struct TYPE_4__ {TYPE_1__ lcp; } ;
struct c67x00_device {TYPE_2__ hpi; } ;

/* Variables and functions */
 int /*<<< orphan*/  COMM_RESET ; 
 int /*<<< orphan*/  hpi_send_mbox (struct c67x00_device*,int /*<<< orphan*/ ) ; 
 int ll_recv_msg (struct c67x00_device*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

int c67x00_ll_reset(struct c67x00_device *dev)
{
	int rc;

	mutex_lock(&dev->hpi.lcp.mutex);
	hpi_send_mbox(dev, COMM_RESET);
	rc = ll_recv_msg(dev);
	mutex_unlock(&dev->hpi.lcp.mutex);

	return rc;
}