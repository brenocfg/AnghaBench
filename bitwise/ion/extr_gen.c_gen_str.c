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
 int* char_to_escape ; 
 int /*<<< orphan*/  gen_indent ; 
 int /*<<< orphan*/  genf (char*,...) ; 
 int /*<<< orphan*/  genln () ; 
 int /*<<< orphan*/  genlnf (char*) ; 
 scalar_t__ isprint (char const) ; 

void gen_str(const char *str, bool multiline) {
    if (multiline) {
        gen_indent++;
        genln();
    }
    genf("\"");
    while (*str) {
        const char *start = str;
        while (*str && isprint(*str) && !char_to_escape[(unsigned char)*str]) {
            str++;
        }
        if (start != str) {
            genf("%.*s", str - start, start);
        }
        if (*str) {
            if (char_to_escape[(unsigned char)*str]) {
                genf("\\%c", char_to_escape[(unsigned char)*str]);
                if (str[0] == '\n' && str[1]) {
                    genf("\"");
                    genlnf("\"");
                }
            } else {
                assert(!isprint(*str));
                genf("\\x%X", (unsigned char)*str);
            }
            str++;
        }
    }
    genf("\"");
    if (multiline) {
        gen_indent--;
    }
}