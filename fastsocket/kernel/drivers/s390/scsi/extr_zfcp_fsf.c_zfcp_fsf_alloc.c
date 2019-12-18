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
struct zfcp_fsf_req {int /*<<< orphan*/ * pool; } ;
typedef  int /*<<< orphan*/  mempool_t ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 struct zfcp_fsf_req* kmalloc (int,int /*<<< orphan*/ ) ; 
 scalar_t__ likely (int /*<<< orphan*/ *) ; 
 struct zfcp_fsf_req* mempool_alloc (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct zfcp_fsf_req*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static struct zfcp_fsf_req *zfcp_fsf_alloc(mempool_t *pool)
{
	struct zfcp_fsf_req *req;

	if (likely(pool))
		req = mempool_alloc(pool, GFP_ATOMIC);
	else
		req = kmalloc(sizeof(*req), GFP_ATOMIC);

	if (unlikely(!req))
		return NULL;

	memset(req, 0, sizeof(*req));
	req->pool = pool;
	return req;
}