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

/* Variables and functions */
 int O_CLOEXEC ; 
 int O_CREAT ; 
 int O_EXCL ; 
 int O_RDWR ; 
 scalar_t__ PATH_MAX ; 
 int /*<<< orphan*/  TEST_PASSCODE ; 
 int /*<<< orphan*/  T_ASSERT_EQ (int,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  T_ASSERT_GE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  T_ASSERT_NE (int,int,char*) ; 
 int /*<<< orphan*/  T_ASSERT_NOTNULL (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  T_ATEND (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  T_LOG (char*,char*) ; 
 int /*<<< orphan*/  T_QUIET ; 
 int /*<<< orphan*/  T_SETUPBEGIN ; 
 int /*<<< orphan*/  T_SETUPEND ; 
 int /*<<< orphan*/  T_SKIP (char*) ; 
 int /*<<< orphan*/  T_WITH_ERRNO ; 
 int /*<<< orphan*/  bzero (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  cleanup ; 
 int /*<<< orphan*/  g_dirpath ; 
 int /*<<< orphan*/  g_fd ; 
 int /*<<< orphan*/  g_filepath ; 
 int /*<<< orphan*/  g_subdirpath ; 
 char* g_test_tempdir ; 
 int has_passcode () ; 
 int /*<<< orphan*/  mkdtemp (char*) ; 
 int /*<<< orphan*/  open (int /*<<< orphan*/ ,int,int) ; 
 int set_passcode (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ strlcat (int /*<<< orphan*/ ,char*,scalar_t__) ; 
 scalar_t__ strlcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int supports_content_prot () ; 

void
setup(void) {
	int ret = 0;
	int local_result = -1;

	T_SETUPBEGIN;

	T_ATEND(cleanup);

	T_WITH_ERRNO;
	T_ASSERT_NOTNULL(
		mkdtemp(g_test_tempdir),
		"Create temporary directory for test"
	);
	T_LOG("Test temp dir: %s", g_test_tempdir);

	T_ASSERT_NE(
		local_result = supports_content_prot(),
		-1,
		"Get content protection support status"
	);

	if(local_result == 0) {
		T_SKIP("Data protection not supported on this system");
	}

	T_ASSERT_EQ(
		has_passcode(),
		0,
		"Device should not have existing passcode"
	);

	T_ASSERT_EQ(
		set_passcode(TEST_PASSCODE, NULL),
		0,
		"Set test passcode"
	);

	bzero(g_filepath, PATH_MAX);
	bzero(g_dirpath, PATH_MAX);
	bzero(g_subdirpath, PATH_MAX);

	ret |= (strlcat(g_filepath, g_test_tempdir, PATH_MAX) == PATH_MAX);
	ret |= (strlcat(g_filepath, "/", PATH_MAX) == PATH_MAX);
	ret |= (strlcpy(g_dirpath, g_filepath, PATH_MAX) == PATH_MAX);
	ret |= (strlcat(g_filepath, "test_file", PATH_MAX) == PATH_MAX);
	ret |= (strlcat(g_dirpath, "test_dir/", PATH_MAX) == PATH_MAX);
	ret |= (strlcpy(g_subdirpath, g_dirpath, PATH_MAX) == PATH_MAX);
	ret |= (strlcat(g_subdirpath, "test_subdir/", PATH_MAX) == PATH_MAX);

	T_QUIET;
	T_ASSERT_EQ(ret, 0, "Initialize test path strings");

	T_WITH_ERRNO;
	T_ASSERT_GE(
		g_fd = open(g_filepath, O_CREAT|O_EXCL|O_RDWR|O_CLOEXEC, 0777),
		0,
		"Create test file"
	);

	T_SETUPEND;
}