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
struct sctp_association {int assoc_id; } ;
typedef  int sctp_assoc_t ;
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 int EAGAIN ; 
 int ENOMEM ; 
 int INT_MAX ; 
 int idr_get_new_above (int /*<<< orphan*/ *,void*,int,int*) ; 
 int idr_low ; 
 int /*<<< orphan*/  idr_pre_get (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sctp_assocs_id ; 
 int /*<<< orphan*/  sctp_assocs_id_lock ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 

int sctp_assoc_set_id(struct sctp_association *asoc, gfp_t gfp)
{
	int assoc_id;
	int error = 0;

	/* If the id is already assigned, keep it. */
	if (asoc->assoc_id)
		return error;
retry:
	if (unlikely(!idr_pre_get(&sctp_assocs_id, gfp)))
		return -ENOMEM;

	spin_lock_bh(&sctp_assocs_id_lock);
	error = idr_get_new_above(&sctp_assocs_id, (void *)asoc,
				    idr_low, &assoc_id);
	if (!error) {
		idr_low = assoc_id + 1;
		if (idr_low == INT_MAX)
			idr_low = 1;
	}
	spin_unlock_bh(&sctp_assocs_id_lock);
	if (error == -EAGAIN)
		goto retry;
	else if (error)
		return error;

	asoc->assoc_id = (sctp_assoc_t) assoc_id;
	return error;
}