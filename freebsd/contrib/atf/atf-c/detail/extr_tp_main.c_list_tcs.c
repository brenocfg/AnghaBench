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
typedef  int /*<<< orphan*/  atf_tp_t ;
typedef  int /*<<< orphan*/  atf_tc_t ;

/* Variables and functions */
 int /*<<< orphan*/  INV (int /*<<< orphan*/ ) ; 
 char** atf_tc_get_md_vars (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/ ** atf_tp_get_tcs (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  atf_utils_free_charpp (char**) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 scalar_t__ strcmp (char*,char*) ; 

__attribute__((used)) static
void
list_tcs(const atf_tp_t *tp)
{
    const atf_tc_t *const *tcs;
    const atf_tc_t *const *tcsptr;

    printf("Content-Type: application/X-atf-tp; version=\"1\"\n\n");

    tcs = atf_tp_get_tcs(tp);
    INV(tcs != NULL);  /* Should be checked. */
    for (tcsptr = tcs; *tcsptr != NULL; tcsptr++) {
        const atf_tc_t *tc = *tcsptr;
        char **vars = atf_tc_get_md_vars(tc);
        char **ptr;

        INV(vars != NULL);  /* Should be checked. */

        if (tcsptr != tcs)  /* Not first. */
            printf("\n");

        for (ptr = vars; *ptr != NULL; ptr += 2) {
            if (strcmp(*ptr, "ident") == 0) {
                printf("ident: %s\n", *(ptr + 1));
                break;
            }
        }

        for (ptr = vars; *ptr != NULL; ptr += 2) {
            if (strcmp(*ptr, "ident") != 0) {
                printf("%s: %s\n", *ptr, *(ptr + 1));
            }
        }

        atf_utils_free_charpp(vars);
    }
}