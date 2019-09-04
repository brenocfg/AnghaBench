#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int block_type; int /*<<< orphan*/ * sb_hybrid; int /*<<< orphan*/  switch_point; } ;
typedef  int /*<<< orphan*/  MPADecodeContext ;
typedef  int /*<<< orphan*/  INTFLOAT ;
typedef  TYPE_1__ GranuleDef ;

/* Variables and functions */
 int /*<<< orphan*/  AA (int) ; 
 int SBLIMIT ; 

__attribute__((used)) static void compute_antialias(MPADecodeContext *s, GranuleDef *g)
{
    INTFLOAT *ptr;
    int n, i;

    /* we antialias only "long" bands */
    if (g->block_type == 2) {
        if (!g->switch_point)
            return;
        /* XXX: check this for 8000Hz case */
        n = 1;
    } else {
        n = SBLIMIT - 1;
    }

    ptr = g->sb_hybrid + 18;
    for (i = n; i > 0; i--) {
        AA(0);
        AA(1);
        AA(2);
        AA(3);
        AA(4);
        AA(5);
        AA(6);
        AA(7);

        ptr += 18;
    }
}