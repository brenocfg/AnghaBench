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
struct stat {int st_mode; } ;
typedef  int /*<<< orphan*/  name_dir2_file ;
typedef  int /*<<< orphan*/  name_dir2 ;
typedef  int /*<<< orphan*/  name_dir1 ;

/* Variables and functions */
 int S_IFDIR ; 
 int S_IFREG ; 
 int /*<<< orphan*/  TEST_ASSERT_EQUAL (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TEST_ASSERT_FALSE (int) ; 
 int /*<<< orphan*/  TEST_ASSERT_TRUE (int) ; 
 int /*<<< orphan*/  mkdir (char*,int) ; 
 int /*<<< orphan*/  rmdir (char*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char const*) ; 
 int /*<<< orphan*/  stat (char*,struct stat*) ; 
 int /*<<< orphan*/  test_fatfs_create_file_with_text (char*,char*) ; 
 int /*<<< orphan*/  unlink (char*) ; 

void test_fatfs_mkdir_rmdir(const char* filename_prefix)
{
    char name_dir1[64];
    char name_dir2[64];
    char name_dir2_file[64];
    snprintf(name_dir1, sizeof(name_dir1), "%s1", filename_prefix);
    snprintf(name_dir2, sizeof(name_dir2), "%s2", filename_prefix);
    snprintf(name_dir2_file, sizeof(name_dir2_file), "%s2/1.txt", filename_prefix);

    TEST_ASSERT_EQUAL(0, mkdir(name_dir1, 0755));
    struct stat st;
    TEST_ASSERT_EQUAL(0, stat(name_dir1, &st));
    TEST_ASSERT_TRUE(st.st_mode & S_IFDIR);
    TEST_ASSERT_FALSE(st.st_mode & S_IFREG);
    TEST_ASSERT_EQUAL(0, rmdir(name_dir1));
    TEST_ASSERT_EQUAL(-1, stat(name_dir1, &st));

    TEST_ASSERT_EQUAL(0, mkdir(name_dir2, 0755));
    test_fatfs_create_file_with_text(name_dir2_file, "foo\n");
    TEST_ASSERT_EQUAL(0, stat(name_dir2, &st));
    TEST_ASSERT_TRUE(st.st_mode & S_IFDIR);
    TEST_ASSERT_FALSE(st.st_mode & S_IFREG);
    TEST_ASSERT_EQUAL(0, stat(name_dir2_file, &st));
    TEST_ASSERT_FALSE(st.st_mode & S_IFDIR);
    TEST_ASSERT_TRUE(st.st_mode & S_IFREG);
    TEST_ASSERT_EQUAL(-1, rmdir(name_dir2));
    TEST_ASSERT_EQUAL(0, unlink(name_dir2_file));
    TEST_ASSERT_EQUAL(0, rmdir(name_dir2));
}