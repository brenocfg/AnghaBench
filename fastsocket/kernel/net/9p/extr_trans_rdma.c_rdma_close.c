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
struct p9_trans_rdma {int /*<<< orphan*/  cm_id; } ;
struct p9_client {int /*<<< orphan*/  status; struct p9_trans_rdma* trans; } ;

/* Variables and functions */
 int /*<<< orphan*/  Disconnected ; 
 int /*<<< orphan*/  rdma_destroy_trans (struct p9_trans_rdma*) ; 
 int /*<<< orphan*/  rdma_disconnect (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void rdma_close(struct p9_client *client)
{
	struct p9_trans_rdma *rdma;

	if (!client)
		return;

	rdma = client->trans;
	if (!rdma)
		return;

	client->status = Disconnected;
	rdma_disconnect(rdma->cm_id);
	rdma_destroy_trans(rdma);
}