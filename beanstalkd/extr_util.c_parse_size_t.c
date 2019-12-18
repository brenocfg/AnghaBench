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
 char sscanf (char*,char*,size_t*,char*) ; 
 int /*<<< orphan*/  usage (int) ; 
 int /*<<< orphan*/  warnx (char*,char*) ; 

__attribute__((used)) static size_t
parse_size_t(char *str)
{
    char r, x;
    size_t size;

    r = sscanf(str, "%zu%c", &size, &x);
    if (1 != r) {
        warnx("invalid size: %s", str);
        usage(5);
    }
    return size;
}