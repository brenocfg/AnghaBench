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
typedef  int uint64_t ;

/* Variables and functions */
 scalar_t__ EINVAL ; 
 scalar_t__ errno ; 
 char* strchr (char*,int) ; 
 int tolower (int /*<<< orphan*/ ) ; 

uint64_t hexToInt(char *p, size_t count) {
    uint64_t value = 0;
    char *charset = "0123456789abcdef";

    errno = 0;
    while(count--) {
        int c = tolower(*p++);
        char *pos = strchr(charset,c);
        int v;
        if (!pos) {
            errno = EINVAL;
            v = 0;
        } else {
            v = pos-charset;
        }
        value = (value << 4) | v;
    }
    return value;
}