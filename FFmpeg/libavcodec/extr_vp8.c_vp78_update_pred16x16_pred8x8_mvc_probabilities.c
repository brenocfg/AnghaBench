#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {TYPE_1__* prob; int /*<<< orphan*/  c; } ;
typedef  TYPE_2__ VP8Context ;
typedef  int /*<<< orphan*/  VP56RangeCoder ;
struct TYPE_4__ {int /*<<< orphan*/ ** mvc; void** pred8x8c; void** pred16x16; } ;

/* Variables and functions */
 scalar_t__ vp56_rac_get_prob_branchy (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ ** vp8_mv_update_prob ; 
 scalar_t__ vp8_rac_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vp8_rac_get_nn (int /*<<< orphan*/ *) ; 
 void* vp8_rac_get_uint (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void vp78_update_pred16x16_pred8x8_mvc_probabilities(VP8Context *s,
                                                            int mvc_size)
{
    VP56RangeCoder *c = &s->c;
    int i, j;

    if (vp8_rac_get(c))
        for (i = 0; i < 4; i++)
            s->prob->pred16x16[i] = vp8_rac_get_uint(c, 8);
    if (vp8_rac_get(c))
        for (i = 0; i < 3; i++)
            s->prob->pred8x8c[i]  = vp8_rac_get_uint(c, 8);

    // 17.2 MV probability update
    for (i = 0; i < 2; i++)
        for (j = 0; j < mvc_size; j++)
            if (vp56_rac_get_prob_branchy(c, vp8_mv_update_prob[i][j]))
                s->prob->mvc[i][j] = vp8_rac_get_nn(c);
}