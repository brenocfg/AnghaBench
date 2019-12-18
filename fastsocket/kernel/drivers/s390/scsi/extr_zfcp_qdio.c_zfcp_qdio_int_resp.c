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
typedef  int u8 ;
typedef  scalar_t__ u64 ;
struct TYPE_4__ {TYPE_1__** sbal; } ;
struct zfcp_qdio {struct zfcp_adapter* adapter; TYPE_2__ resp_q; } ;
struct zfcp_adapter {int /*<<< orphan*/  dbf; } ;
struct qdio_buffer_element {scalar_t__ scount; scalar_t__ addr; } ;
struct ccw_device {int dummy; } ;
struct TYPE_3__ {struct qdio_buffer_element* element; } ;

/* Variables and functions */
 int FSF_MAX_SBALS_PER_REQ ; 
 int QDIO_MAX_BUFFERS_PER_Q ; 
 int /*<<< orphan*/  memset (void**,int /*<<< orphan*/ ,int) ; 
 int min (scalar_t__,int) ; 
 scalar_t__ unlikely (unsigned int) ; 
 scalar_t__ zfcp_adapter_multi_buffer_active (struct zfcp_adapter*) ; 
 int /*<<< orphan*/  zfcp_dbf_hba_qdio (int /*<<< orphan*/ ,unsigned int,int,int,scalar_t__,int,void**) ; 
 int /*<<< orphan*/  zfcp_fsf_reqid_check (struct zfcp_qdio*,int) ; 
 int /*<<< orphan*/  zfcp_qdio_handler_error (struct zfcp_qdio*,char*,unsigned int) ; 
 int /*<<< orphan*/  zfcp_qdio_resp_put_back (struct zfcp_qdio*,int) ; 

__attribute__((used)) static void zfcp_qdio_int_resp(struct ccw_device *cdev, unsigned int qdio_err,
			       int queue_no, int first, int count,
			       unsigned long parm)
{
	struct zfcp_qdio *qdio = (struct zfcp_qdio *) parm;
	struct zfcp_adapter *adapter = qdio->adapter;
	struct qdio_buffer_element *sbale;
	int sbal_no, sbal_idx;
	void *pl[FSF_MAX_SBALS_PER_REQ + 1];
	u64 req_id = 0;
	u8 scount = 0;

	if (unlikely(qdio_err)) {
		memset(pl, 0, (FSF_MAX_SBALS_PER_REQ + 1) * sizeof(void *));
		if (zfcp_adapter_multi_buffer_active(adapter)) {
			sbale = qdio->resp_q.sbal[first]->element;
			req_id = (u64) sbale->addr;
			scount = min(sbale->scount + 1,
				     FSF_MAX_SBALS_PER_REQ + 1);
				     /* incl. signaling SBAL */

			for (sbal_no = 0; sbal_no < scount; sbal_no++) {
				sbal_idx = (first + sbal_no) %
					QDIO_MAX_BUFFERS_PER_Q;
				pl[sbal_no] = qdio->resp_q.sbal[sbal_idx];
			}
		}
		zfcp_dbf_hba_qdio(qdio->adapter->dbf, qdio_err, first,
				  count, req_id, scount,
				  zfcp_adapter_multi_buffer_active(adapter)
				  ? pl : NULL);
		zfcp_qdio_handler_error(qdio, "qdires1", qdio_err);
		return;
	}

	/*
	 * go through all SBALs from input queue currently
	 * returned by QDIO layer
	 */
	for (sbal_no = 0; sbal_no < count; sbal_no++) {
		sbal_idx = (first + sbal_no) % QDIO_MAX_BUFFERS_PER_Q;
		/* go through all SBALEs of SBAL */
		zfcp_fsf_reqid_check(qdio, sbal_idx);
	}

	/*
	 * put range of SBALs back to response queue
	 * (including SBALs which have already been free before)
	 */
	zfcp_qdio_resp_put_back(qdio, count);
}