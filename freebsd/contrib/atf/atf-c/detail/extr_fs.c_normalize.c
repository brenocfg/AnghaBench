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
typedef  int /*<<< orphan*/  atf_dynstr_t ;

/* Variables and functions */
 int /*<<< orphan*/  PRE (int) ; 
 int /*<<< orphan*/  atf_dynstr_append_fmt (int /*<<< orphan*/ *,char*,...) ; 
 scalar_t__ atf_dynstr_length (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atf_is_error (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atf_no_error () ; 
 scalar_t__ strlen (char const*) ; 
 char* strtok_r (char*,char*,char**) ; 

__attribute__((used)) static
atf_error_t
normalize(atf_dynstr_t *d, char *p)
{
    const char *ptr;
    char *last;
    atf_error_t err;
    bool first;

    PRE(strlen(p) > 0);
    PRE(atf_dynstr_length(d) == 0);

    if (p[0] == '/')
        err = atf_dynstr_append_fmt(d, "/");
    else
        err = atf_no_error();

    first = true;
    last = NULL; /* Silence GCC warning. */
    ptr = strtok_r(p, "/", &last);
    while (!atf_is_error(err) && ptr != NULL) {
        if (strlen(ptr) > 0) {
            err = atf_dynstr_append_fmt(d, "%s%s", first ? "" : "/", ptr);
            first = false;
        }

        ptr = strtok_r(NULL, "/", &last);
    }

    return err;
}