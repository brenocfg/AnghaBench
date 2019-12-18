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
 int /*<<< orphan*/  strlcpy (char*,char const*,int) ; 
 int strlen (char*) ; 

bool btc_config_get_str(const char *section, const char *key, char *value, int *size_bytes)
{
    assert(config != NULL);
    assert(section != NULL);
    assert(key != NULL);
    assert(value != NULL);
    assert(size_bytes != NULL);

    const char *stored_value = config_get_string(config, section, key, NULL);

    if (!stored_value) {
        return false;
    }

    strlcpy(value, stored_value, *size_bytes);
    *size_bytes = strlen(value) + 1;

    return true;
}