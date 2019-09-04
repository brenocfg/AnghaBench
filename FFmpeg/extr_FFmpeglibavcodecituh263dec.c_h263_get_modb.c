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
typedef  int /*<<< orphan*/  GetBitContext ;

/* Variables and functions */
 int get_bits (int /*<<< orphan*/ *,int) ; 
 int get_bits1 (int /*<<< orphan*/ *) ; 
 int get_unary (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int h263_get_modb(GetBitContext *gb, int pb_frame, int *cbpb)
{
    int c, mv = 1;

    if (pb_frame < 3) { // h.263 Annex G and i263 PB-frame
        c = get_bits1(gb);
        if (pb_frame == 2 && c)
            mv = !get_bits1(gb);
    } else { // h.263 Annex M improved PB-frame
        mv = get_unary(gb, 0, 4) + 1;
        c = mv & 1;
        mv = !!(mv & 2);
    }
    if(c)
        *cbpb = get_bits(gb, 6);
    return mv;
}