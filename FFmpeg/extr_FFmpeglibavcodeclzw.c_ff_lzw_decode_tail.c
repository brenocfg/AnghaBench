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
struct LZWState {scalar_t__ mode; scalar_t__ bs; int /*<<< orphan*/  gb; } ;
typedef  int /*<<< orphan*/  LZWState ;

/* Variables and functions */
 scalar_t__ FF_LZW_GIF ; 
 scalar_t__ bytestream2_get_byte (int /*<<< orphan*/ *) ; 
 scalar_t__ bytestream2_get_bytes_left (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bytestream2_skip (int /*<<< orphan*/ *,scalar_t__) ; 
 int bytestream2_tell (int /*<<< orphan*/ *) ; 

int ff_lzw_decode_tail(LZWState *p)
{
    struct LZWState *s = (struct LZWState *)p;

    if(s->mode == FF_LZW_GIF) {
        while (s->bs > 0 && bytestream2_get_bytes_left(&s->gb)) {
            bytestream2_skip(&s->gb, s->bs);
            s->bs = bytestream2_get_byte(&s->gb);
        }
    }else
        bytestream2_skip(&s->gb, bytestream2_get_bytes_left(&s->gb));
    return bytestream2_tell(&s->gb);
}