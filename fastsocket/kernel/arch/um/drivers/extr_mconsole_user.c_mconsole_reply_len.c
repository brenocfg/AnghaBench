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
struct sockaddr {int dummy; } ;
struct mconsole_reply {int err; int more; char* data; int len; } ;
struct mc_request {int /*<<< orphan*/  originlen; scalar_t__ origin; int /*<<< orphan*/  originating_fd; } ;
typedef  int /*<<< orphan*/  reply ;

/* Variables and functions */
 scalar_t__ MCONSOLE_MAX_DATA ; 
 int MIN (int,scalar_t__) ; 
 int errno ; 
 int /*<<< orphan*/  memcpy (char*,char const*,int) ; 
 int sendto (int /*<<< orphan*/ ,struct mconsole_reply*,int,int /*<<< orphan*/ ,struct sockaddr*,int /*<<< orphan*/ ) ; 

int mconsole_reply_len(struct mc_request *req, const char *str, int total,
		       int err, int more)
{
	/*
	 * XXX This is a stack consumption problem.  It'd be nice to
	 * make it global and serialize access to it, but there are a
	 * ton of callers to this function.
	 */
	struct mconsole_reply reply;
	int len, n;

	do {
		reply.err = err;

		/* err can only be true on the first packet */
		err = 0;

		len = MIN(total, MCONSOLE_MAX_DATA - 1);

		if (len == total) reply.more = more;
		else reply.more = 1;

		memcpy(reply.data, str, len);
		reply.data[len] = '\0';
		total -= len;
		str += len;
		reply.len = len + 1;

		len = sizeof(reply) + reply.len - sizeof(reply.data);

		n = sendto(req->originating_fd, &reply, len, 0,
			   (struct sockaddr *) req->origin, req->originlen);

		if (n < 0)
			return -errno;
	} while (total > 0);
	return 0;
}