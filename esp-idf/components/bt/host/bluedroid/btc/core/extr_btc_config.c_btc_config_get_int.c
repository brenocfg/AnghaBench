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
 int config_get_int (int /*<<< orphan*/ *,char const*,char const*,int) ; 
 int config_has_key (int /*<<< orphan*/ *,char const*,char const*) ; 

bool btc_config_get_int(const char *section, const char *key, int *value)
{
    assert(config != NULL);
    assert(section != NULL);
    assert(key != NULL);
    assert(value != NULL);

    bool ret = config_has_key(config, section, key);
    if (ret) {
        *value = config_get_int(config, section, key, *value);
    }

    return ret;
}