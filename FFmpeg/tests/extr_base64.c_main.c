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
 int EOF ; 
 int getchar () ; 
 int /*<<< orphan*/  putb64 () ; 
 int /*<<< orphan*/  putchar (char) ; 

int main(void)
{
    static const char b64[] =
        "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
    unsigned i_bits = 0;
    int i_shift     = 0;
    int out_len     = 0;
    int in;

#define putb64()                                        \
    do {                                                \
        putchar(b64[(i_bits << 6 >> i_shift) & 0x3f]);  \
        out_len++;                                      \
        i_shift -= 6;                                   \
    } while (0)

    while ((in = getchar()) != EOF) {
        i_bits   = (i_bits << 8) + in;
        i_shift += 8;
        while (i_shift > 6)
            putb64();
    }
    while (i_shift > 0)
        putb64();
    while (out_len++ & 3)
        putchar('=');
    putchar('\n');

    return 0;
}