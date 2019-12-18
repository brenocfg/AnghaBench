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
 int /*<<< orphan*/  atf_is_error (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atf_no_error () ; 
 int /*<<< orphan*/  atf_no_memory_error () ; 
 int /*<<< orphan*/  free (char*) ; 
 char* strdup (char const*) ; 
 char* strtok_r (char*,char const*,char**) ; 

atf_error_t
atf_text_for_each_word(const char *instr, const char *sep,
                       atf_error_t (*func)(const char *, void *),
                       void *data)
{
    atf_error_t err;
    char *str, *str2, *last;

    str = strdup(instr);
    if (str == NULL) {
        err = atf_no_memory_error();
        goto out;
    }

    err = atf_no_error();
    str2 = strtok_r(str, sep, &last);
    while (str2 != NULL && !atf_is_error(err)) {
        err = func(str2, data);
        str2 = strtok_r(NULL, sep, &last);
    }

    free(str);
out:
    return err;
}