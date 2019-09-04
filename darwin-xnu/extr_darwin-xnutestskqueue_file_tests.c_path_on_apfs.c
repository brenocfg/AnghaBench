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
struct statfs {int /*<<< orphan*/ * f_fstypename; } ;

/* Variables and functions */
 int /*<<< orphan*/  T_ASSERT_POSIX_SUCCESS (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  T_QUIET ; 
 scalar_t__ memcmp (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  statfs (char const*,struct statfs*) ; 
 int /*<<< orphan*/  strlen (char*) ; 

__attribute__((used)) static bool
path_on_apfs(const char *path)
{
	struct statfs sfs = {};
	T_QUIET; T_ASSERT_POSIX_SUCCESS(statfs(path, &sfs), NULL);
	return (memcmp(&sfs.f_fstypename[0], "apfs", strlen("apfs")) == 0);
}