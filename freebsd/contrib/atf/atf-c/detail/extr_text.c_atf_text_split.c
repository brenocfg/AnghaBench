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
typedef  int /*<<< orphan*/  atf_dynstr_t ;

/* Variables and functions */
 int /*<<< orphan*/  INV (int) ; 
 int /*<<< orphan*/  atf_dynstr_fini_disown (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atf_dynstr_init_raw (int /*<<< orphan*/ *,char const*,int) ; 
 scalar_t__ atf_is_error (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atf_list_append (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  atf_list_fini (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atf_list_init (int /*<<< orphan*/ *) ; 
 int strlen (char const*) ; 
 char* strstr (char const*,char const*) ; 

atf_error_t
atf_text_split(const char *str, const char *delim, atf_list_t *words)
{
    atf_error_t err;
    const char *end;
    const char *iter;

    err = atf_list_init(words);
    if (atf_is_error(err))
        goto err;

    end = str + strlen(str);
    INV(*end == '\0');
    iter = str;
    while (iter < end) {
        const char *ptr;

        INV(iter != NULL);
        ptr = strstr(iter, delim);
        if (ptr == NULL)
            ptr = end;

        INV(ptr >= iter);
        if (ptr > iter) {
            atf_dynstr_t word;

            err = atf_dynstr_init_raw(&word, iter, ptr - iter);
            if (atf_is_error(err))
                goto err_list;

            err = atf_list_append(words, atf_dynstr_fini_disown(&word), true);
            if (atf_is_error(err))
                goto err_list;
        }

        iter = ptr + strlen(delim);
    }

    INV(!atf_is_error(err));
    return err;

err_list:
    atf_list_fini(words);
err:
    return err;
}