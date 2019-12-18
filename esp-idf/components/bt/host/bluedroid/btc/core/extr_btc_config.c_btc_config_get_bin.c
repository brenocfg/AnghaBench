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
typedef  scalar_t__ uint8_t ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * config ; 
 char* config_get_string (int /*<<< orphan*/ *,char const*,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  isxdigit (unsigned char) ; 
 int /*<<< orphan*/  sscanf (char const*,char*,unsigned int*) ; 
 size_t strlen (char const*) ; 

bool btc_config_get_bin(const char *section, const char *key, uint8_t *value, size_t *length)
{
    assert(config != NULL);
    assert(section != NULL);
    assert(key != NULL);
    assert(value != NULL);
    assert(length != NULL);

    const char *value_str = config_get_string(config, section, key, NULL);

    if (!value_str) {
        return false;
    }

    size_t value_len = strlen(value_str);
    if ((value_len % 2) != 0 || *length < (value_len / 2)) {
        return false;
    }

    for (size_t i = 0; i < value_len; ++i)
        if (!isxdigit((unsigned char)value_str[i])) {
            return false;
        }

    for (*length = 0; *value_str; value_str += 2, *length += 1) {
        unsigned int val;
        sscanf(value_str, "%02x", &val);
        value[*length] = (uint8_t)(val);
    }

    return true;
}