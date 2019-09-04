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
 int /*<<< orphan*/  SPACE_CHARS ; 
 int av_toupper (unsigned char) ; 
 int /*<<< orphan*/  strspn (char const*,int /*<<< orphan*/ ) ; 

int ff_hex_to_data(uint8_t *data, const char *p)
{
    int c, len, v;

    len = 0;
    v   = 1;
    for (;;) {
        p += strspn(p, SPACE_CHARS);
        if (*p == '\0')
            break;
        c = av_toupper((unsigned char) *p++);
        if (c >= '0' && c <= '9')
            c = c - '0';
        else if (c >= 'A' && c <= 'F')
            c = c - 'A' + 10;
        else
            break;
        v = (v << 4) | c;
        if (v & 0x100) {
            if (data)
                data[len] = v;
            len++;
            v = 1;
        }
    }
    return len;
}