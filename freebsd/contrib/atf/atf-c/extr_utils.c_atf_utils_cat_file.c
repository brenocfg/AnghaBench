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
typedef  size_t ssize_t ;
typedef  int /*<<< orphan*/  buffer ;

/* Variables and functions */
 int /*<<< orphan*/  ATF_REQUIRE (int) ; 
 int /*<<< orphan*/  ATF_REQUIRE_MSG (int,char*,char const*) ; 
 int /*<<< orphan*/  O_RDONLY ; 
 int open (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,char const*) ; 
 size_t read (int const,char*,int) ; 
 char* strchr (char*,char) ; 

void
atf_utils_cat_file(const char *name, const char *prefix)
{
    const int fd = open(name, O_RDONLY);
    ATF_REQUIRE_MSG(fd != -1, "Cannot open %s", name);

    char buffer[1024];
    ssize_t count;
    bool continued = false;
    while ((count = read(fd, buffer, sizeof(buffer) - 1)) > 0) {
        buffer[count] = '\0';

        if (!continued)
            printf("%s", prefix);

        char *iter = buffer;
        char *end;
        while ((end = strchr(iter, '\n')) != NULL) {
            *end = '\0';
            printf("%s\n", iter);

            iter = end + 1;
            if (iter != buffer + count)
                printf("%s", prefix);
            else
                continued = false;
        }
        if (iter < buffer + count) {
            printf("%s", iter);
            continued = true;
        }
    }
    ATF_REQUIRE(count == 0);
}