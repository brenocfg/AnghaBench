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
struct ubsan_violation {int /*<<< orphan*/  loc; } ;

/* Variables and functions */
 int /*<<< orphan*/  panic (char*,char*) ; 
 int /*<<< orphan*/  printf (char*,char*) ; 
 scalar_t__ ubsan_format (struct ubsan_violation*,char*,size_t const) ; 
 int /*<<< orphan*/  ubsan_loc_acquire (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ubsan_log_append (struct ubsan_violation*) ; 
 scalar_t__ ubsan_print ; 

__attribute__((used)) static void
ubsan_handle(struct ubsan_violation *v, bool fatal)
{
	const size_t sz = 256;
	static char buf[sz];
	size_t n = 0;
	buf[0] = '\0';

	if (!ubsan_loc_acquire(v->loc)) {
		/* violation site already reported */
		return;
	}

	ubsan_log_append(v);

	if (ubsan_print || fatal) {
		n += ubsan_format(v, buf+n, sz-n);
	}

	if (ubsan_print) {
		printf("UBSan: %s", buf);
	}

	if (fatal) {
		panic("UBSan: %s", buf);
	}
}