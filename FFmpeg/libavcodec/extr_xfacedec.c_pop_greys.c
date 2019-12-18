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
typedef  int /*<<< orphan*/  BigInt ;

/* Variables and functions */
 int XFACE_WIDTH ; 
 int /*<<< orphan*/  ff_xface_probranges_2x2 ; 
 int pop_integer (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void pop_greys(BigInt *b, char *bitmap, int w, int h)
{
    if (w > 3) {
        w /= 2;
        h /= 2;
        pop_greys(b, bitmap,                       w, h);
        pop_greys(b, bitmap + w,                   w, h);
        pop_greys(b, bitmap + XFACE_WIDTH * h,     w, h);
        pop_greys(b, bitmap + XFACE_WIDTH * h + w, w, h);
    } else {
        w = pop_integer(b, ff_xface_probranges_2x2);
        if (w & 1) bitmap[0]               = 1;
        if (w & 2) bitmap[1]               = 1;
        if (w & 4) bitmap[XFACE_WIDTH]     = 1;
        if (w & 8) bitmap[XFACE_WIDTH + 1] = 1;
    }
}