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
struct nfs_direct_req {int /*<<< orphan*/  completion; scalar_t__ iocb; scalar_t__ count; scalar_t__ error; } ;

/* Variables and functions */
 int /*<<< orphan*/  aio_complete (scalar_t__,long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  complete_all (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nfs_direct_req_release (struct nfs_direct_req*) ; 

__attribute__((used)) static void nfs_direct_complete(struct nfs_direct_req *dreq)
{
	if (dreq->iocb) {
		long res = (long) dreq->error;
		if (!res)
			res = (long) dreq->count;
		aio_complete(dreq->iocb, res, 0);
	}
	complete_all(&dreq->completion);

	nfs_direct_req_release(dreq);
}