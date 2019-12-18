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
struct stat {int /*<<< orphan*/  st_mode; } ;

/* Variables and functions */
 scalar_t__ ENOENT ; 
 int /*<<< orphan*/  S_ISFIFO (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  T_ASSERT_FAIL (char*,char const*) ; 
 int /*<<< orphan*/  T_ASSERT_POSIX_ZERO (int,char*,char const*) ; 
 int /*<<< orphan*/  T_ASSERT_TRUE (int /*<<< orphan*/ ,char*,char const*) ; 
 scalar_t__ errno ; 
 int mkfifo (char const*,int) ; 
 int stat (char const*,struct stat*) ; 

void
create_fifo(const char * filepath)
{
	struct stat f_stat;
	int ret = 0;
	errno   = 0;
	ret = stat(filepath, &f_stat);
	if (ret == 0) {
		/* if file exists, make sure its a fifo */
		T_ASSERT_TRUE(S_ISFIFO(f_stat.st_mode), "ensure %s is a fifo", filepath);
	} else if (errno == ENOENT) {
		ret = mkfifo(filepath, 0777);
		T_ASSERT_POSIX_ZERO(ret, "creating a fifo at path %s", filepath);
	} else {
		T_ASSERT_FAIL("stat operation on %s", filepath);
	}
}