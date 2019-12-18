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
struct TYPE_2__ {double float_val; int /*<<< orphan*/  suffix; int /*<<< orphan*/  kind; } ;

/* Variables and functions */
 double HUGE_VAL ; 
 int /*<<< orphan*/  SUFFIX_D ; 
 int /*<<< orphan*/  TOKEN_FLOAT ; 
 int /*<<< orphan*/  error_here (char*,...) ; 
 scalar_t__ isdigit (char) ; 
 char* stream ; 
 double strtod (char const*,int /*<<< orphan*/ *) ; 
 TYPE_1__ token ; 
 char tolower (char) ; 

void scan_float(void) {
    const char *start = stream;
    while (isdigit(*stream)) {
        stream++;
    }
    if (*stream == '.') {
        stream++;
    }
    while (isdigit(*stream)) {
        stream++;
    }
    if (tolower(*stream) == 'e') {
        stream++;
        if (*stream == '+' || *stream == '-') {
            stream++;
        }
        if (!isdigit(*stream)) {
            error_here("Expected digit after float literal exponent, found '%c'.", *stream);
        }
        while (isdigit(*stream)) {
            stream++;
        }
    }
    double val = strtod(start, NULL);
    if (val == HUGE_VAL) {
        error_here("Float literal overflow");
    }
    token.kind = TOKEN_FLOAT;
    token.float_val = val;
    if (tolower(*stream) == 'd') {
        token.suffix = SUFFIX_D;
        stream++;
    }
}