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
typedef  int uint8_t ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void btc_key_value_to_string(uint8_t *key_value, char *value_str, int key_length)
{
    const char *lookup = "0123456789abcdef";

    assert(key_value != NULL);
    assert(value_str != NULL);

    for (size_t i = 0; i < key_length; ++i) {
        value_str[(i * 2) + 0] = lookup[(key_value[i] >> 4) & 0x0F];
        value_str[(i * 2) + 1] = lookup[key_value[i] & 0x0F];
    }

    return;
}