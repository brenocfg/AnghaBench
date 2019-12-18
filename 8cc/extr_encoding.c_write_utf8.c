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
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  Buffer ;

/* Variables and functions */
 int /*<<< orphan*/  buf_write (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  error (char*,int) ; 

void write_utf8(Buffer *b, uint32_t rune) {
    if (rune < 0x80) {
        buf_write(b, rune);
        return;
    }
    if (rune < 0x800) {
        buf_write(b, 0xC0 | (rune >> 6));
        buf_write(b, 0x80 | (rune & 0x3F));
        return;
    }
    if (rune < 0x10000) {
        buf_write(b, 0xE0 | (rune >> 12));
        buf_write(b, 0x80 | ((rune >> 6) & 0x3F));
        buf_write(b, 0x80 | (rune & 0x3F));
        return;
    }
    if (rune < 0x200000) {
        buf_write(b, 0xF0 | (rune >> 18));
        buf_write(b, 0x80 | ((rune >> 12) & 0x3F));
        buf_write(b, 0x80 | ((rune >> 6) & 0x3F));
        buf_write(b, 0x80 | (rune & 0x3F));
        return;
    }
    error("invalid UCS character: \\U%08x", rune);
}