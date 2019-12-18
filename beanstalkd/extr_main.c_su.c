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
struct passwd {int /*<<< orphan*/  pw_uid; int /*<<< orphan*/  pw_gid; } ;

/* Variables and functions */
 scalar_t__ errno ; 
 int /*<<< orphan*/  exit (int) ; 
 struct passwd* getpwnam (char const*) ; 
 int setgid (int /*<<< orphan*/ ) ; 
 int setuid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  twarn (char*,char const*,...) ; 
 int /*<<< orphan*/  twarnx (char*,char const*) ; 

__attribute__((used)) static void
su(const char *user) 
{
    errno = 0;
    struct passwd *pwent = getpwnam(user);
    if (errno) {
        twarn("getpwnam(\"%s\")", user);
        exit(32);
    }
    if (!pwent) {
        twarnx("getpwnam(\"%s\"): no such user", user);
        exit(33);
    }

    int r = setgid(pwent->pw_gid);
    if (r == -1) {
        twarn("setgid(%d \"%s\")", pwent->pw_gid, user);
        exit(34);
    }

    r = setuid(pwent->pw_uid);
    if (r == -1) {
        twarn("setuid(%d \"%s\")", pwent->pw_uid, user);
        exit(34);
    }
}