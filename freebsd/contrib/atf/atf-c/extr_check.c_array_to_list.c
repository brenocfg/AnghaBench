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
typedef  int /*<<< orphan*/  atf_list_t ;
typedef  int /*<<< orphan*/  atf_error_t ;

/* Variables and functions */
 scalar_t__ atf_is_error (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atf_list_append (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  atf_list_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atf_no_memory_error () ; 
 char* strdup (char const* const) ; 

__attribute__((used)) static
atf_error_t
array_to_list(const char *const *a, atf_list_t *l)
{
    atf_error_t err;

    err = atf_list_init(l);
    if (atf_is_error(err))
        goto out;

    while (*a != NULL) {
        char *item = strdup(*a);
        if (item == NULL) {
            err = atf_no_memory_error();
            goto out;
        }

        err = atf_list_append(l, item, true);
        if (atf_is_error(err))
            goto out;

        a++;
    }

out:
    return err;
}