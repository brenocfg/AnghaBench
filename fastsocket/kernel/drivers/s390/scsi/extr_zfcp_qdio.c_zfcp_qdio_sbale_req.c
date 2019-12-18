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
struct zfcp_queue_req {int /*<<< orphan*/  sbal_last; } ;
struct zfcp_qdio {int /*<<< orphan*/  req_q; } ;
struct qdio_buffer_element {int dummy; } ;

/* Variables and functions */
 struct qdio_buffer_element* zfcp_qdio_sbale (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

struct qdio_buffer_element *zfcp_qdio_sbale_req(struct zfcp_qdio *qdio,
						struct zfcp_queue_req *q_req)
{
	return zfcp_qdio_sbale(&qdio->req_q, q_req->sbal_last, 0);
}