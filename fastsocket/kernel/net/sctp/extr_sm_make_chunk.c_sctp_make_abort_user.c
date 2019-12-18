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
struct sctp_chunk {int dummy; } ;
struct sctp_association {int dummy; } ;
struct msghdr {int /*<<< orphan*/  msg_iov; } ;
typedef  int /*<<< orphan*/  sctp_errhdr_t ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  SCTP_ERROR_USER_ABORT ; 
 int /*<<< orphan*/  kfree (void*) ; 
 void* kmalloc (size_t,int /*<<< orphan*/ ) ; 
 int memcpy_fromiovec (void*,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  sctp_addto_chunk (struct sctp_chunk*,size_t,void*) ; 
 int /*<<< orphan*/  sctp_chunk_free (struct sctp_chunk*) ; 
 int /*<<< orphan*/  sctp_init_cause (struct sctp_chunk*,int /*<<< orphan*/ ,size_t) ; 
 struct sctp_chunk* sctp_make_abort (struct sctp_association const*,int /*<<< orphan*/ *,int) ; 

struct sctp_chunk *sctp_make_abort_user(const struct sctp_association *asoc,
					const struct msghdr *msg,
					size_t paylen)
{
	struct sctp_chunk *retval;
	void *payload = NULL;
	int err;

	retval = sctp_make_abort(asoc, NULL, sizeof(sctp_errhdr_t) + paylen);
	if (!retval)
		goto err_chunk;

	if (paylen) {
		/* Put the msg_iov together into payload.  */
		payload = kmalloc(paylen, GFP_KERNEL);
		if (!payload)
			goto err_payload;

		err = memcpy_fromiovec(payload, msg->msg_iov, paylen);
		if (err < 0)
			goto err_copy;
	}

	sctp_init_cause(retval, SCTP_ERROR_USER_ABORT, paylen);
	sctp_addto_chunk(retval, paylen, payload);

	if (paylen)
		kfree(payload);

	return retval;

err_copy:
	kfree(payload);
err_payload:
	sctp_chunk_free(retval);
	retval = NULL;
err_chunk:
	return retval;
}