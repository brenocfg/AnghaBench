#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {unsigned long long int_val; int /*<<< orphan*/  suffix; int /*<<< orphan*/  kind; int /*<<< orphan*/  mod; } ;

/* Variables and functions */
 int /*<<< orphan*/  MOD_BIN ; 
 int /*<<< orphan*/  MOD_HEX ; 
 int /*<<< orphan*/  MOD_OCT ; 
 int /*<<< orphan*/  SUFFIX_L ; 
 int /*<<< orphan*/  SUFFIX_LL ; 
 int /*<<< orphan*/  SUFFIX_U ; 
 int /*<<< orphan*/  SUFFIX_UL ; 
 int /*<<< orphan*/  SUFFIX_ULL ; 
 int /*<<< orphan*/  TOKEN_INT ; 
 int ULLONG_MAX ; 
 int* char_to_digit ; 
 int /*<<< orphan*/  error_here (char*,...) ; 
 scalar_t__ isdigit (char) ; 
 char* stream ; 
 TYPE_1__ token ; 
 char tolower (char) ; 

void scan_int(void) {
    int base = 10;
    const char *start_digits = stream;
    if (*stream == '0') {
        stream++;
        if (tolower(*stream) == 'x') {
            stream++;
            token.mod = MOD_HEX;
            base = 16;
            start_digits = stream;
        } else if (tolower(*stream) == 'b') {
            stream++;
            token.mod = MOD_BIN;
            base = 2;
            start_digits = stream;
        } else if (isdigit(*stream)) {
            token.mod = MOD_OCT;
            base = 8;
            start_digits = stream;
        }
    }
    unsigned long long val = 0;
    for (;;) {
        if (*stream == '_') {
            stream++;
            continue;
        }
        int digit = char_to_digit[(unsigned char)*stream];
        if (digit == 0 && *stream != '0') {
            break;
        }
        if (digit >= base) {
            error_here("Digit '%c' out of range for base %d", *stream, base);
            digit = 0;
        }
        if (val > (ULLONG_MAX - digit)/base) {
            error_here("Integer literal overflow");
            while (isdigit(*stream)) {
                stream++;
            }
            val = 0;
            break;
        }
        val = val*base + digit;
        stream++;
    }
    if (stream == start_digits) {
        error_here("Expected base %d digit, got '%c'", base, *stream);
    }
    token.kind = TOKEN_INT;
    token.int_val = val;
    if (tolower(*stream) == 'u') {
        token.suffix = SUFFIX_U;
        stream++;
        if (tolower(*stream) == 'l') {
            token.suffix = SUFFIX_UL;
            stream++;
            if (tolower(*stream) == 'l') {
                token.suffix = SUFFIX_ULL;
                stream++;
            }
        }
    } else if (tolower(*stream) == 'l') {
        token.suffix = SUFFIX_L;
        stream++;
        if (tolower(*stream) == 'l') {
            token.suffix = SUFFIX_LL;
            stream++;
        }
    }
}