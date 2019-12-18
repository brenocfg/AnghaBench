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
 unsigned int get_bits (int /*<<< orphan*/ *,int) ; 
 unsigned int get_bits1 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * map_1bit ; 
 int /*<<< orphan*/ * map_2bit_far ; 
 int /*<<< orphan*/  set_pos (TYPE_1__*,unsigned int,unsigned int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int k34(InterplayACMContext *s, unsigned ind, unsigned col)
{
    GetBitContext *gb = &s->gb;
    unsigned i, b;

    for (i = 0; i < s->rows; i++) {
        b = get_bits1(gb);
        if (b == 0) {
            set_pos(s, i, col, 0);
            continue;
        }

        b = get_bits1(gb);
        if (b == 0) {
            b = get_bits1(gb);
            set_pos(s, i, col, map_1bit[b]);
            continue;
        }

        b = get_bits(gb, 2);
        set_pos(s, i, col, map_2bit_far[b]);
    }
    return 0;
}