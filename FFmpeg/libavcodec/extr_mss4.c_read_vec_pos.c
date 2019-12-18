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
 scalar_t__ get_bits1 (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void read_vec_pos(GetBitContext *gb, int *vec_pos, int *sel_flag,
                         int *sel_len, int *prev)
{
    int i, y_flag = 0;

    for (i = 2; i >= 0; i--) {
        if (!sel_flag[i]) {
            vec_pos[i] = 0;
            continue;
        }
        if ((!i && !y_flag) || get_bits1(gb)) {
            if (sel_len[i] > 0) {
                int pval = prev[i];
                vec_pos[i] = get_bits(gb, sel_len[i]);
                if (vec_pos[i] >= pval)
                    vec_pos[i]++;
            } else {
                vec_pos[i] = !prev[i];
            }
            y_flag = 1;
        } else {
            vec_pos[i] = prev[i];
        }
    }
}