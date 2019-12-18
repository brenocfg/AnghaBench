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
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * config ; 
 char* config_get_string (int /*<<< orphan*/ *,char const*,char const*,int /*<<< orphan*/ *) ; 
 size_t strlen (char const*) ; 

size_t btc_config_get_bin_length(const char *section, const char *key)
{
    assert(config != NULL);
    assert(section != NULL);
    assert(key != NULL);

    const char *value_str = config_get_string(config, section, key, NULL);

    if (!value_str) {
        return 0;
    }

    size_t value_len = strlen(value_str);
    return ((value_len % 2) != 0) ? 0 : (value_len / 2);
}