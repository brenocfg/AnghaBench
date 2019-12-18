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
 unsigned char* char_to_escape ; 
 int /*<<< orphan*/  genf (char*,unsigned char) ; 
 scalar_t__ isprint (char) ; 

void gen_char(char c) {
    if (char_to_escape[(unsigned char)c]) {
        genf("'\\%c'", char_to_escape[(unsigned char)c]);
    } else if (isprint(c)) {
        genf("'%c'", c);
    } else {
        genf("'\\x%X'", (unsigned char)c);
    }
}