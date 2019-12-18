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
typedef  int time_t ;
struct utimbuf {void* modtime; int /*<<< orphan*/  actime; } ;
struct tm {int tm_mon; int tm_mday; int tm_year; int tm_hour; int tm_min; int tm_sec; } ;
struct timeval {int tv_sec; } ;
struct stat {int st_mtime; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  TEST_ASSERT (int) ; 
 int /*<<< orphan*/  TEST_ASSERT_EQUAL (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TEST_ASSERT_EQUAL_UINT32 (void*,int) ; 
 int /*<<< orphan*/  TEST_ASSERT_NOT_EQUAL (void*,int) ; 
 char* asctime (struct tm*) ; 
 char* ctime (int*) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  memset (struct tm*,int /*<<< orphan*/ ,int) ; 
 void* mktime (struct tm*) ; 
 int /*<<< orphan*/  printf (char*,char*) ; 
 int /*<<< orphan*/  settimeofday (struct timeval*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stat (char const*,struct stat*) ; 
 int /*<<< orphan*/  test_fatfs_create_file_with_text (char const*,char*) ; 
 int /*<<< orphan*/  utime (char const*,struct utimbuf*) ; 

void test_fatfs_utime(const char* filename, const char* root_dir)
{
    struct stat achieved_stat;
    struct tm desired_tm;
    struct utimbuf desired_time = {
        .actime = 0, // access time is not supported
        .modtime = 0,
    };
    time_t false_now = 0;
    memset(&desired_tm, 0, sizeof(struct tm));

    {
        // Setting up a false actual time - used when the file is created and for modification with the current time
        desired_tm.tm_mon = 10 - 1;
        desired_tm.tm_mday = 31;
        desired_tm.tm_year = 2018 - 1900;
        desired_tm.tm_hour = 10;
        desired_tm.tm_min = 35;
        desired_tm.tm_sec = 23;

        false_now = mktime(&desired_tm);

        struct timeval now = { .tv_sec = false_now };
        settimeofday(&now, NULL);
    }
    test_fatfs_create_file_with_text(filename, "");

    // 00:00:00. January 1st, 1980 - FATFS cannot handle earlier dates
    desired_tm.tm_mon = 1 - 1;
    desired_tm.tm_mday = 1;
    desired_tm.tm_year = 1980 - 1900;
    desired_tm.tm_hour = 0;
    desired_tm.tm_min = 0;
    desired_tm.tm_sec = 0;
    printf("Testing mod. time: %s", asctime(&desired_tm));
    desired_time.modtime = mktime(&desired_tm);
    TEST_ASSERT_EQUAL(0, utime(filename, &desired_time));
    TEST_ASSERT_EQUAL(0, stat(filename, &achieved_stat));
    TEST_ASSERT_EQUAL_UINT32(desired_time.modtime, achieved_stat.st_mtime);

    // current time
    TEST_ASSERT_EQUAL(0, utime(filename, NULL));
    TEST_ASSERT_EQUAL(0, stat(filename, &achieved_stat));
    printf("Mod. time changed to (false actual time): %s", ctime(&achieved_stat.st_mtime));
    TEST_ASSERT_NOT_EQUAL(desired_time.modtime, achieved_stat.st_mtime);
    TEST_ASSERT(false_now - achieved_stat.st_mtime <= 2); // two seconds of tolerance are given

    // 23:59:08. December 31st, 2037
    desired_tm.tm_mon = 12 - 1;
    desired_tm.tm_mday = 31;
    desired_tm.tm_year = 2037 - 1900;
    desired_tm.tm_hour = 23;
    desired_tm.tm_min = 59;
    desired_tm.tm_sec = 8;
    printf("Testing mod. time: %s", asctime(&desired_tm));
    desired_time.modtime = mktime(&desired_tm);
    TEST_ASSERT_EQUAL(0, utime(filename, &desired_time));
    TEST_ASSERT_EQUAL(0, stat(filename, &achieved_stat));
    TEST_ASSERT_EQUAL_UINT32(desired_time.modtime, achieved_stat.st_mtime);

    //WARNING: it has the Unix Millenium bug (Y2K38)

    // 00:00:00. January 1st, 1970 - FATFS cannot handle years before 1980
    desired_tm.tm_mon = 1 - 1;
    desired_tm.tm_mday = 1;
    desired_tm.tm_year = 1970 - 1900;
    desired_tm.tm_hour = 0;
    desired_tm.tm_min = 0;
    desired_tm.tm_sec = 0;
    printf("Testing mod. time: %s", asctime(&desired_tm));
    desired_time.modtime = mktime(&desired_tm);
    TEST_ASSERT_EQUAL(-1, utime(filename, &desired_time));
    TEST_ASSERT_EQUAL(EINVAL, errno);
}