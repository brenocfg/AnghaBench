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
typedef  int /*<<< orphan*/  atf_error_t ;

/* Variables and functions */
 scalar_t__ EINVAL ; 
 scalar_t__ ERANGE ; 
 long LONG_MAX ; 
 long LONG_MIN ; 
 int /*<<< orphan*/  atf_libc_error (scalar_t__,char*,char const*) ; 
 int /*<<< orphan*/  atf_no_error () ; 
 scalar_t__ errno ; 
 long strtol (char const*,char**,int) ; 

atf_error_t
atf_text_to_long(const char *str, long *l)
{
    atf_error_t err;
    char *endptr;
    long tmp;

    errno = 0;
    tmp = strtol(str, &endptr, 10);
    if (str[0] == '\0' || *endptr != '\0')
        err = atf_libc_error(EINVAL, "'%s' is not a number", str);
    else if (errno == ERANGE || (tmp == LONG_MAX || tmp == LONG_MIN))
        err = atf_libc_error(ERANGE, "'%s' is out of range", str);
    else {
        *l = tmp;
        err = atf_no_error();
    }

    return err;
}