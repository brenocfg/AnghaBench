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
struct LZWState {scalar_t__ bbits; scalar_t__ cursize; int end_code; scalar_t__ mode; int bs; int bbuf; int curmask; int /*<<< orphan*/  gb; } ;

/* Variables and functions */
 scalar_t__ FF_LZW_GIF ; 
 int bytestream2_get_byte (int /*<<< orphan*/ *) ; 
 scalar_t__ bytestream2_get_bytes_left (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int lzw_get_code(struct LZWState * s)
{
    int c;

    if (s->bbits < s->cursize && bytestream2_get_bytes_left(&s->gb) <= 0)
        return s->end_code;

    if(s->mode == FF_LZW_GIF) {
        while (s->bbits < s->cursize) {
            if (!s->bs) {
                s->bs = bytestream2_get_byte(&s->gb);
            }
            s->bbuf |= bytestream2_get_byte(&s->gb) << s->bbits;
            s->bbits += 8;
            s->bs--;
        }
        c = s->bbuf;
        s->bbuf >>= s->cursize;
    } else { // TIFF
        while (s->bbits < s->cursize) {
            s->bbuf = (s->bbuf << 8) | bytestream2_get_byte(&s->gb);
            s->bbits += 8;
        }
        c = s->bbuf >> (s->bbits - s->cursize);
    }
    s->bbits -= s->cursize;
    return c & s->curmask;
}