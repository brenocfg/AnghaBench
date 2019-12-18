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
typedef  int ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  ATF_REQUIRE (int) ; 
 int /*<<< orphan*/  ATF_REQUIRE_MSG (int,char*,char const*) ; 
 int /*<<< orphan*/  O_RDONLY ; 
 int /*<<< orphan*/  close (int const) ; 
 int open (char const*,int /*<<< orphan*/ ) ; 
 int read (int const,void* const,size_t const) ; 

__attribute__((used)) static ssize_t
read_file(const char *path, void *const buffer, const size_t buflen)
{
    const int fd = open(path, O_RDONLY);
    ATF_REQUIRE_MSG(fd != -1, "Cannot open %s", path);
    const ssize_t length = read(fd, buffer, buflen - 1);
    close(fd);
    ATF_REQUIRE(length != -1);
    ((char *)buffer)[length] = '\0';
    return length;
}