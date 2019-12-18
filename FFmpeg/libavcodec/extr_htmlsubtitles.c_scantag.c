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

__attribute__((used)) static int scantag(const char* in, char* buffer, int* lenp) {
    int len;

    for (len = 0; len < 128; len++) {
        const char c = *in++;
        switch (c) {
        case '\0':
            return 0;
        case '<':
            return 0;
        case '>':
            buffer[len] = '\0';
            *lenp = len+1;
            return 1;
        default:
            break;
        }
        buffer[len] = c;
    }
    return 0;
}