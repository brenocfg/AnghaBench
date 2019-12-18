#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int* midbuf; int /*<<< orphan*/  gb; } ;
typedef  TYPE_1__ InterplayACMContext ;
typedef  int /*<<< orphan*/  GetBitContext ;

/* Variables and functions */
 int fill_block (TYPE_1__*) ; 
 int get_bits (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  juggle_block (TYPE_1__*) ; 

__attribute__((used)) static int decode_block(InterplayACMContext *s)
{
    GetBitContext *gb = &s->gb;
    int pwr, count, val, i, x, ret;

    pwr = get_bits(gb, 4);
    val = get_bits(gb, 16);

    count = 1 << pwr;

    for (i = 0, x = 0; i < count; i++) {
        s->midbuf[i] = x;
        x += val;
    }

    for (i = 1, x = -val; i <= count; i++) {
        s->midbuf[-i] = x;
        x -= (unsigned)val;
    }

    ret = fill_block(s);
    if (ret < 0)
        return ret;

    juggle_block(s);

    return 0;
}