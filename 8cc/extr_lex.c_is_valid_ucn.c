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

__attribute__((used)) static bool is_valid_ucn(unsigned int c) {
    // C11 6.4.3p2: U+D800 to U+DFFF are reserved for surrogate pairs.
    // A codepoint within the range cannot be a valid character.
    if (0xD800 <= c && c <= 0xDFFF)
        return false;
    // It's not allowed to encode ASCII characters using \U or \u.
    // Some characters not in the basic character set (C11 5.2.1p3)
    // are allowed as exceptions.
    return 0xA0 <= c || c == '$' || c == '@' || c == '`';
}