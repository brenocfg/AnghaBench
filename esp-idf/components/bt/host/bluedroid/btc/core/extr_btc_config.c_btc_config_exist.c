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
 int config_has_key (int /*<<< orphan*/ *,char const*,char const*) ; 

bool btc_config_exist(const char *section, const char *key)
{
    assert(config != NULL);
    assert(section != NULL);
    assert(key != NULL);

    return config_has_key(config, section, key);
}