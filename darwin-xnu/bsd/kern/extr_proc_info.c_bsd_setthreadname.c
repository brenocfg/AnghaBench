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
struct uthread {int /*<<< orphan*/  pth_name; } ;

/* Variables and functions */
 scalar_t__ MAXTHREADNAMESIZE ; 
 int /*<<< orphan*/  OSCompareAndSwapPtr (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TRACE_STRING_THREADNAME ; 
 int /*<<< orphan*/  TRACE_STRING_THREADNAME_PREV ; 
 int /*<<< orphan*/  assert (char*) ; 
 int /*<<< orphan*/  bzero (char*,scalar_t__) ; 
 char* kalloc (scalar_t__) ; 
 int /*<<< orphan*/  kernel_debug_string_simple (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (char*,scalar_t__) ; 
 int /*<<< orphan*/  strncpy (int /*<<< orphan*/ ,char const*,scalar_t__) ; 

void
bsd_setthreadname(void *uth, const char *name) {
	struct uthread *ut = (struct uthread *)uth;
	char * name_buf = NULL;

	if (!ut->pth_name) {
		/* If there is no existing thread name, allocate a buffer for one. */
		name_buf = kalloc(MAXTHREADNAMESIZE);
		assert(name_buf);
		bzero(name_buf, MAXTHREADNAMESIZE);

		/* Someone could conceivably have named the thread at the same time we did. */
		if (!OSCompareAndSwapPtr(NULL, name_buf, &ut->pth_name)) {
			kfree(name_buf, MAXTHREADNAMESIZE);
		}
	} else {
		kernel_debug_string_simple(TRACE_STRING_THREADNAME_PREV, ut->pth_name);
	}

	strncpy(ut->pth_name, name, MAXTHREADNAMESIZE - 1);
	kernel_debug_string_simple(TRACE_STRING_THREADNAME, ut->pth_name);
}