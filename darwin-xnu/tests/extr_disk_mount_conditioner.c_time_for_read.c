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
typedef  scalar_t__ uint64_t ;
typedef  int /*<<< orphan*/  ssize_t ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int READSIZE ; 
 int /*<<< orphan*/  SEEK_SET ; 
 int /*<<< orphan*/  T_ASSERT_EQ_INT (int /*<<< orphan*/ ,int,char*) ; 
 int /*<<< orphan*/  T_ASSERT_EQ_LONG (int /*<<< orphan*/ ,int,char*,int) ; 
 int /*<<< orphan*/  T_ASSERT_GE_LONG (int /*<<< orphan*/ ,long,char*) ; 
 int /*<<< orphan*/  bzero (char*,int) ; 
 scalar_t__ dt_nanoseconds () ; 
 int /*<<< orphan*/  lseek (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int memcmp (char*,char const*,int) ; 
 int /*<<< orphan*/  read (int,char*,int) ; 

__attribute__((used)) static uint64_t time_for_read(int fd, const char *expected) {
	int err;
	ssize_t ret;
	char buf[READSIZE];
	uint64_t start, stop;

	bzero(buf, sizeof(buf));
	lseek(fd, 0, SEEK_SET);

	start = dt_nanoseconds();
	ret = read(fd, buf, READSIZE);
	stop = dt_nanoseconds();

	T_ASSERT_GE_LONG(ret, 0L, "read from temporary file");
	T_ASSERT_EQ_LONG(ret, READSIZE, "read %ld bytes from temporary file", READSIZE);
	err = memcmp(buf, expected, sizeof(buf));
	T_ASSERT_EQ_INT(0, err, "read expected contents from temporary file");

	return (stop - start);
}