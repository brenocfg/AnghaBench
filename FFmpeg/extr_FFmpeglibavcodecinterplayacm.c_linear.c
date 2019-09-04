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
 int get_bits (int /*<<< orphan*/ *,unsigned int) ; 
 int /*<<< orphan*/  set_pos (TYPE_1__*,unsigned int,unsigned int,int) ; 

__attribute__((used)) static int linear(InterplayACMContext *s, unsigned ind, unsigned col)
{
    GetBitContext *gb = &s->gb;
    unsigned int i;
    int b, middle = 1 << (ind - 1);

    for (i = 0; i < s->rows; i++) {
        b = get_bits(gb, ind);
        set_pos(s, i, col, b - middle);
    }
    return 0;
}