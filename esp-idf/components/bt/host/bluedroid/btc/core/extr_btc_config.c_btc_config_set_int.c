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
 int /*<<< orphan*/  config_set_int (int /*<<< orphan*/ *,char const*,char const*,int) ; 

bool btc_config_set_int(const char *section, const char *key, int value)
{
    assert(config != NULL);
    assert(section != NULL);
    assert(key != NULL);

    config_set_int(config, section, key, value);

    return true;
}