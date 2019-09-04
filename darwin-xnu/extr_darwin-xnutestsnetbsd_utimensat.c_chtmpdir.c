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
struct statfs {int /*<<< orphan*/ * f_fstypename; int /*<<< orphan*/  member_0; } ;

/* Variables and functions */
 int /*<<< orphan*/  DIRPATH ; 
 int /*<<< orphan*/  FILEPATH ; 
 int /*<<< orphan*/  LINK ; 
 int /*<<< orphan*/  T_ASSERT_POSIX_SUCCESS (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  T_ASSERT_POSIX_ZERO (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  T_QUIET ; 
 int /*<<< orphan*/  T_SETUPBEGIN ; 
 int /*<<< orphan*/  T_SETUPEND ; 
 int /*<<< orphan*/  T_SKIP (char*) ; 
 int /*<<< orphan*/  chdir (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dt_tmpdir () ; 
 scalar_t__ memcmp (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rmdir (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  statfs (char*,struct statfs*) ; 
 int /*<<< orphan*/  strlen (char*) ; 
 int /*<<< orphan*/  unlink (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void chtmpdir(void)
{
	T_SETUPBEGIN;
	T_ASSERT_POSIX_ZERO(chdir(dt_tmpdir()), NULL);

	// <rdar://problem/31780295> dt_tmpdir() should guarantee a clean directory for each run
	unlink(FILEPATH);
	unlink(LINK);
	rmdir(DIRPATH);

	// Skip the test if the current working directory is not on APFS.
	struct statfs sfs = { 0 };
	T_QUIET; T_ASSERT_POSIX_SUCCESS(statfs(".", &sfs), NULL);
	if (memcmp(&sfs.f_fstypename[0], "apfs", strlen("apfs")) != 0) {
		T_SKIP("utimensat is APFS-only, but working directory is non-APFS");
	}

	T_SETUPEND;
}