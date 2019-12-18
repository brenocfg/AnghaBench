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
typedef  scalar_t__ ssize_t ;
typedef  int /*<<< orphan*/  buffer ;

/* Variables and functions */
 int /*<<< orphan*/  ATF_REQUIRE_MSG (int,char*,char const*) ; 
 int /*<<< orphan*/  O_RDONLY ; 
 int /*<<< orphan*/  close (int const) ; 
 scalar_t__ memcmp (char const*,char*,scalar_t__) ; 
 int open (char const*,int /*<<< orphan*/ ) ; 
 scalar_t__ read (int const,char*,int) ; 
 scalar_t__ strlen (char const*) ; 

bool
atf_utils_compare_file(const char *name, const char *contents)
{
    const int fd = open(name, O_RDONLY);
    ATF_REQUIRE_MSG(fd != -1, "Cannot open %s", name);

    const char *pos = contents;
    ssize_t remaining = strlen(contents);

    char buffer[1024];
    ssize_t count;
    while ((count = read(fd, buffer, sizeof(buffer))) > 0 &&
           count <= remaining) {
        if (memcmp(pos, buffer, count) != 0) {
            close(fd);
            return false;
        }
        remaining -= count;
        pos += count;
    }
    close(fd);
    return count == 0 && remaining == 0;
}