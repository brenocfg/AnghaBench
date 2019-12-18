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
typedef  int /*<<< orphan*/  MotionVector ;
typedef  int /*<<< orphan*/  AVLFG ;

/* Variables and functions */
 int /*<<< orphan*/  check_subset (int /*<<< orphan*/ *) ; 
 int rand_in (int /*<<< orphan*/ ,int const,int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool get_subset(
    AVLFG *alfg,
    const MotionVector *point_pairs,
    const int num_point_pairs,
    MotionVector *pairs_subset,
    int max_attempts
) {
    int idx[3];
    int i = 0, j, iters = 0;

    for (; iters < max_attempts; iters++) {
        for (i = 0; i < 3 && iters < max_attempts;) {
            int idx_i = 0;

            for (;;) {
                idx_i = idx[i] = rand_in(0, num_point_pairs, alfg);

                for (j = 0; j < i; j++) {
                    if (idx_i == idx[j]) {
                        break;
                    }
                }

                if (j == i) {
                    break;
                }
            }

            pairs_subset[i] = point_pairs[idx[i]];
            i++;
        }

        if (i == 3 && !check_subset(pairs_subset)) {
            continue;
        }
        break;
    }

    return i == 3 && iters < max_attempts;
}