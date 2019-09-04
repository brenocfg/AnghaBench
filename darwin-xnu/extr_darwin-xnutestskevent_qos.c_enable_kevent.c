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
typedef  int /*<<< orphan*/  uint64_t ;
struct kevent_qos_s {int /*<<< orphan*/  member_0; } ;
typedef  int /*<<< orphan*/  kern_return_t ;

/* Variables and functions */
 int KEVENT_FLAG_DYNAMIC_KQ_MUST_EXIST ; 
 int KEVENT_FLAG_ERROR_EVENTS ; 
 int KEVENT_FLAG_WORKLOOP ; 
 int /*<<< orphan*/  T_ASSERT_POSIX_SUCCESS (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  T_QUIET ; 
 int /*<<< orphan*/  kevent_id (int /*<<< orphan*/ ,struct kevent_qos_s*,int,struct kevent_qos_s*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  populate_kevent (struct kevent_qos_s*,unsigned long long) ; 

__attribute__((used)) static void
enable_kevent(uint64_t *workloop_id, unsigned long long port)
{
	kern_return_t kr;
	struct kevent_qos_s kev;

	populate_kevent(&kev, port);
	struct kevent_qos_s kev_err[] = {{ 0 }};

	kr = kevent_id(*workloop_id, &kev, 1, kev_err, 1, NULL,
			NULL, KEVENT_FLAG_WORKLOOP | KEVENT_FLAG_ERROR_EVENTS | KEVENT_FLAG_DYNAMIC_KQ_MUST_EXIST);
	T_QUIET; T_ASSERT_POSIX_SUCCESS(kr, "kevent_id");
}