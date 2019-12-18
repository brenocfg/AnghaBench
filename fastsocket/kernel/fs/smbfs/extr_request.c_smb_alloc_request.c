#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct smb_sb_info {int /*<<< orphan*/  nr_requests; } ;
struct smb_request {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  policy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ERESTARTSYS ; 
 struct smb_request* ERR_PTR (int /*<<< orphan*/ ) ; 
 scalar_t__ MAX_REQUEST_HARD ; 
 int /*<<< orphan*/  SCHED_YIELD ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 TYPE_1__* current ; 
 scalar_t__ fatal_signal_pending (TYPE_1__*) ; 
 scalar_t__ nfs_try_to_free_pages (struct smb_sb_info*) ; 
 int /*<<< orphan*/  schedule () ; 
 struct smb_request* smb_do_alloc_request (struct smb_sb_info*,int) ; 

struct smb_request *smb_alloc_request(struct smb_sb_info *server, int bufsize)
{
	struct smb_request *req = NULL;

	for (;;) {
		atomic_inc(&server->nr_requests);
		if (atomic_read(&server->nr_requests) <= MAX_REQUEST_HARD) {
			req = smb_do_alloc_request(server, bufsize);
			if (req != NULL)
				break;
		}

#if 0
		/*
		 * Try to free up at least one request in order to stay
		 * below the hard limit
		 */
                if (nfs_try_to_free_pages(server))
			continue;

		if (fatal_signal_pending(current))
			return ERR_PTR(-ERESTARTSYS);
		current->policy = SCHED_YIELD;
		schedule();
#else
		/* FIXME: we want something like nfs does above, but that
		   requires changes to all callers and can wait. */
		break;
#endif
	}
	return req;
}