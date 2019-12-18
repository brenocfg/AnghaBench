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
typedef  int /*<<< orphan*/  atf_map_t ;
typedef  int /*<<< orphan*/  atf_error_t ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  INV (int /*<<< orphan*/ ) ; 
 scalar_t__ atf_is_error (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atf_libc_error (int /*<<< orphan*/ ,char*,char const*) ; 
 int /*<<< orphan*/  atf_map_fini (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atf_map_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atf_map_insert (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  strdup (char const*) ; 

atf_error_t
atf_map_init_charpp(atf_map_t *m, const char *const *array)
{
    atf_error_t err;
    const char *const *ptr = array;

    err = atf_map_init(m);
    if (array != NULL) {
        while (!atf_is_error(err) && *ptr != NULL) {
            const char *key, *value;

            key = *ptr;
            INV(key != NULL);
            ptr++;

            if ((value = *ptr) == NULL) {
                err = atf_libc_error(EINVAL, "List too short; no value for "
                    "key '%s' provided", key);  /* XXX: Not really libc_error */
                break;
            }
            ptr++;

            err = atf_map_insert(m, key, strdup(value), true);
        }
    }

    if (atf_is_error(err))
        atf_map_fini(m);

    return err;
}