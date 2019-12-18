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
 int /*<<< orphan*/  assert (int) ; 
 int* char_to_digit ; 
 int /*<<< orphan*/  error_here (char*) ; 
 char* stream ; 

int scan_hex_escape(void) {
    assert(*stream == 'x');
    stream++;
    int val = char_to_digit[(unsigned char)*stream];
    if (!val && *stream != '0') {
        error_here("\\x needs at least 1 hex digit");
    }
    stream++;
    int digit = char_to_digit[(unsigned char)*stream];
    if (digit || *stream == '0') {
        val *= 16;
        val += digit;
        if (val > 0xFF) {
            error_here("\\x argument out of range");
            val = 0xFF;
        }
        stream++;
    }
    return val;
}