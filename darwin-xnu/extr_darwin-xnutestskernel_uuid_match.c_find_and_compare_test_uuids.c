#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uuid_t ;
struct stat {int st_mode; } ;
struct TYPE_4__ {int gl_matchc; char** gl_pathv; } ;
typedef  TYPE_1__ glob_t ;

/* Variables and functions */
 int S_IFREG ; 
 int /*<<< orphan*/  T_ASSERT_EQ (int,int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  T_ASSERT_POSIX_SUCCESS (int,char*,char*) ; 
 int /*<<< orphan*/  T_EXPECT_TRUE (int,char*) ; 
 int /*<<< orphan*/  T_LOG (char*,char*) ; 
 int /*<<< orphan*/  T_WITH_ERRNO ; 
 int glob (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  globfree (TYPE_1__*) ; 
 scalar_t__ parse_binary_uuid (char*,int /*<<< orphan*/ ) ; 
 int stat (char*,struct stat*) ; 
 scalar_t__ uuid_compare (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void find_and_compare_test_uuids(char *search_path, uuid_t kuuid) {
	glob_t g;
	int ret = glob(search_path, 0, NULL, &g);
	T_WITH_ERRNO; T_ASSERT_EQ(ret, 0, "glob %s", search_path);

	bool pass = false;
	for (int i = 0; i < g.gl_matchc; i++) {
		char *path = g.gl_pathv[i];

		//check that [path] is the path for a file (not a directory, device, etc.)
		struct stat s;
		int ret = stat(path, &s);
		T_ASSERT_POSIX_SUCCESS(ret, "stat %s", path);
		if ((s.st_mode & S_IFREG) == 0) {
			continue;
		}

		T_LOG("Reading file at path: %s", path);
		uuid_t tuuid;
		if (parse_binary_uuid(path, tuuid) &&
				uuid_compare(kuuid, tuuid) == 0) {
			pass = true;
			break;
		}
	}
	globfree(&g);
	T_EXPECT_TRUE(pass, "The sources match");
}