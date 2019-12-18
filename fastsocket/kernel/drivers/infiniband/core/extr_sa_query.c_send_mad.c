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
struct ib_sa_query {int id; TYPE_1__* mad_buf; } ;
typedef  int /*<<< orphan*/  gfp_t ;
struct TYPE_2__ {int timeout_ms; struct ib_sa_query** context; } ;

/* Variables and functions */
 int EAGAIN ; 
 int ENOMEM ; 
 int ib_post_send_mad (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int idr_get_new (int /*<<< orphan*/ *,struct ib_sa_query*,int*) ; 
 int /*<<< orphan*/  idr_lock ; 
 int /*<<< orphan*/  idr_pre_get (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  idr_remove (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  query_idr ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int send_mad(struct ib_sa_query *query, int timeout_ms, gfp_t gfp_mask)
{
	unsigned long flags;
	int ret, id;

retry:
	if (!idr_pre_get(&query_idr, gfp_mask))
		return -ENOMEM;
	spin_lock_irqsave(&idr_lock, flags);
	ret = idr_get_new(&query_idr, query, &id);
	spin_unlock_irqrestore(&idr_lock, flags);
	if (ret == -EAGAIN)
		goto retry;
	if (ret)
		return ret;

	query->mad_buf->timeout_ms  = timeout_ms;
	query->mad_buf->context[0] = query;
	query->id = id;

	ret = ib_post_send_mad(query->mad_buf, NULL);
	if (ret) {
		spin_lock_irqsave(&idr_lock, flags);
		idr_remove(&query_idr, id);
		spin_unlock_irqrestore(&idr_lock, flags);
	}

	/*
	 * It's not safe to dereference query any more, because the
	 * send may already have completed and freed the query in
	 * another context.
	 */
	return ret ? ret : id;
}