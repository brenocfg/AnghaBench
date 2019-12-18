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
typedef  int /*<<< orphan*/  uid_t ;
struct passwd {int /*<<< orphan*/  pw_gid; int /*<<< orphan*/  pw_uid; } ;
typedef  int /*<<< orphan*/  gid_t ;

/* Variables and functions */
 int /*<<< orphan*/  INVOKER_GID ; 
 int /*<<< orphan*/  INVOKER_UID ; 
 int /*<<< orphan*/  T_ASSERT_NOTNULL (struct passwd*,char*) ; 
 int /*<<< orphan*/  T_ASSERT_POSIX_SUCCESS (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  T_QUIET ; 
 int /*<<< orphan*/  T_WITH_ERRNO ; 
 int /*<<< orphan*/  _get_sudo_invoker (int /*<<< orphan*/ ) ; 
 struct passwd* getpwnam (char*) ; 
 int /*<<< orphan*/  setgid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  setuid (int /*<<< orphan*/ ) ; 

void
drop_priv(void)
{
#if TARGET_OS_OSX
    uid_t lower_uid = _get_sudo_invoker(INVOKER_UID);
    gid_t lower_gid = _get_sudo_invoker(INVOKER_GID);
#else
    struct passwd *pw = getpwnam("mobile");
    T_QUIET; T_WITH_ERRNO; T_ASSERT_NOTNULL(pw, "getpwnam(\"mobile\")");
    uid_t lower_uid = pw->pw_uid;
    gid_t lower_gid = pw->pw_gid;
#endif
    T_ASSERT_POSIX_SUCCESS(setgid(lower_gid), "Change group to %u", lower_gid);
    T_ASSERT_POSIX_SUCCESS(setuid(lower_uid), "Change user to %u", lower_uid);
}