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
typedef  int /*<<< orphan*/  u16 ;
struct c67x00_lcp_int_data {int /*<<< orphan*/ * regs; } ;
struct TYPE_3__ {int /*<<< orphan*/  mutex; } ;
struct TYPE_4__ {TYPE_1__ lcp; } ;
struct c67x00_device {TYPE_2__ hpi; } ;

/* Variables and functions */
 int /*<<< orphan*/  COMM_EXEC_INT ; 
 int /*<<< orphan*/  COMM_INT_NUM ; 
 int /*<<< orphan*/  COMM_R (int) ; 
 int COMM_REGS ; 
 int /*<<< orphan*/  hpi_send_mbox (struct c67x00_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hpi_write_word (struct c67x00_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ll_recv_msg (struct c67x00_device*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int c67x00_comm_exec_int(struct c67x00_device *dev, u16 nr,
				struct c67x00_lcp_int_data *data)
{
	int i, rc;

	mutex_lock(&dev->hpi.lcp.mutex);
	hpi_write_word(dev, COMM_INT_NUM, nr);
	for (i = 0; i < COMM_REGS; i++)
		hpi_write_word(dev, COMM_R(i), data->regs[i]);
	hpi_send_mbox(dev, COMM_EXEC_INT);
	rc = ll_recv_msg(dev);
	mutex_unlock(&dev->hpi.lcp.mutex);

	return rc;
}