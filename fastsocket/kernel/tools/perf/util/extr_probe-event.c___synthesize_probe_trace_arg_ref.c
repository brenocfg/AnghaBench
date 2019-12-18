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
struct probe_trace_arg_ref {int /*<<< orphan*/  offset; struct probe_trace_arg_ref* next; } ;

/* Variables and functions */
 int e_snprintf (char*,size_t,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int __synthesize_probe_trace_arg_ref(struct probe_trace_arg_ref *ref,
					     char **buf, size_t *buflen,
					     int depth)
{
	int ret;
	if (ref->next) {
		depth = __synthesize_probe_trace_arg_ref(ref->next, buf,
							 buflen, depth + 1);
		if (depth < 0)
			goto out;
	}

	ret = e_snprintf(*buf, *buflen, "%+ld(", ref->offset);
	if (ret < 0)
		depth = ret;
	else {
		*buf += ret;
		*buflen -= ret;
	}
out:
	return depth;

}