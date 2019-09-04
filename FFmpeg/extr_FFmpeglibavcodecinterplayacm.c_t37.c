#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {unsigned int rows; int /*<<< orphan*/  gb; } ;
typedef  TYPE_1__ InterplayACMContext ;
typedef  int /*<<< orphan*/  GetBitContext ;

/* Variables and functions */
 int AVERROR_INVALIDDATA ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  av_log (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,unsigned int) ; 
 unsigned int get_bits (int /*<<< orphan*/ *,int) ; 
 int* mul_2x11 ; 
 int /*<<< orphan*/  set_pos (TYPE_1__*,unsigned int,unsigned int,int) ; 

__attribute__((used)) static int t37(InterplayACMContext *s, unsigned ind, unsigned col)
{
    GetBitContext *gb = &s->gb;
    unsigned i, b;
    int n1, n2;
    for (i = 0; i < s->rows; i++) {
        /* b = (x1) + (x2 * 11) */
        b = get_bits(gb, 7);
        if (b > 120) {
            av_log(NULL, AV_LOG_ERROR, "Too large b = %d > 120\n", b);
            return AVERROR_INVALIDDATA;
        }

        n1 =  (mul_2x11[b] & 0x0F) - 5;
        n2 = ((mul_2x11[b] >> 4) & 0x0F) - 5;

        set_pos(s, i++, col, n1);
        if (i >= s->rows)
            break;
        set_pos(s, i, col, n2);
    }
    return 0;
}