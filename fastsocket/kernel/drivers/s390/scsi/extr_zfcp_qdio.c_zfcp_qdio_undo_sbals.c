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
struct zfcp_queue_req {int sbal_first; int sbal_last; } ;
struct TYPE_2__ {struct qdio_buffer** sbal; } ;
struct zfcp_qdio {TYPE_1__ req_q; } ;
struct qdio_buffer {int dummy; } ;

/* Variables and functions */
 int QDIO_MAX_BUFFERS_PER_Q ; 
 int /*<<< orphan*/  zfcp_qdio_zero_sbals (struct qdio_buffer**,int,int) ; 

__attribute__((used)) static void zfcp_qdio_undo_sbals(struct zfcp_qdio *qdio,
				 struct zfcp_queue_req *q_req)
{
	struct qdio_buffer **sbal = qdio->req_q.sbal;
	int first = q_req->sbal_first;
	int last = q_req->sbal_last;
	int count = (last - first + QDIO_MAX_BUFFERS_PER_Q) %
		QDIO_MAX_BUFFERS_PER_Q + 1;
	zfcp_qdio_zero_sbals(sbal, first, count);
}