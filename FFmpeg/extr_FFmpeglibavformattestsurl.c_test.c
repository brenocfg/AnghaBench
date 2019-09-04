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
typedef  int /*<<< orphan*/  buf2 ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  ff_make_absolute_url (char*,int,char const*,char const*) ; 
 int /*<<< orphan*/  printf (char*,char const*,...) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char const*) ; 
 scalar_t__ strcmp (char*,char*) ; 

__attribute__((used)) static void test(const char *base, const char *rel)
{
    char buf[200], buf2[200];
    ff_make_absolute_url(buf, sizeof(buf), base, rel);
    printf("%s\n", buf);
    if (base) {
        /* Test in-buffer replacement */
        snprintf(buf2, sizeof(buf2), "%s", base);
        ff_make_absolute_url(buf2, sizeof(buf2), buf2, rel);
        if (strcmp(buf, buf2)) {
            printf("In-place handling of %s + %s failed\n", base, rel);
            exit(1);
        }
    }
}