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
struct ctx {int nr; int id; int eid; int sid; int err; } ;

/* Variables and functions */
 int /*<<< orphan*/  __synccall (int /*<<< orphan*/ ,struct ctx*) ; 
 int /*<<< orphan*/  do_setxid ; 
 scalar_t__ errno ; 

int __setxid(int nr, int id, int eid, int sid)
{
	/* err is initially nonzero so that failure of the first thread does not
	 * trigger the safety kill above. */
	struct ctx c = { .nr = nr, .id = id, .eid = eid, .sid = sid, .err = -1 };
	__synccall(do_setxid, &c);
	if (c.err) {
		if (c.err>0) errno = c.err;
		return -1;
	}
	return 0;
}