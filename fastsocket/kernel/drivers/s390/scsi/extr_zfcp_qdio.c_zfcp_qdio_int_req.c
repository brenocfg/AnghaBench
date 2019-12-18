#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct zfcp_qdio_queue {int /*<<< orphan*/  count; int /*<<< orphan*/  sbal; } ;
struct zfcp_qdio {int /*<<< orphan*/  req_q_wq; TYPE_1__* adapter; struct zfcp_qdio_queue req_q; } ;
struct ccw_device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  dbf; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_add (int,int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (unsigned int) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zfcp_dbf_hba_qdio (int /*<<< orphan*/ ,unsigned int,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zfcp_qdio_account (struct zfcp_qdio*) ; 
 int /*<<< orphan*/  zfcp_qdio_handler_error (struct zfcp_qdio*,char*,unsigned int) ; 
 int /*<<< orphan*/  zfcp_qdio_zero_sbals (int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static void zfcp_qdio_int_req(struct ccw_device *cdev, unsigned int qdio_err,
			      int queue_no, int first, int count,
			      unsigned long parm)
{
	struct zfcp_qdio *qdio = (struct zfcp_qdio *) parm;
	struct zfcp_qdio_queue *queue = &qdio->req_q;

	if (unlikely(qdio_err)) {
		zfcp_dbf_hba_qdio(qdio->adapter->dbf, qdio_err, first,
				  count, 0, 0, NULL);
		zfcp_qdio_handler_error(qdio, "qdireq1", qdio_err);
		return;
	}

	/* cleanup all SBALs being program-owned now */
	zfcp_qdio_zero_sbals(queue->sbal, first, count);

	zfcp_qdio_account(qdio);
	atomic_add(count, &queue->count);
	wake_up(&qdio->req_q_wq);
}