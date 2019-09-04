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
struct wavesynth_context {int* pink_pool; int /*<<< orphan*/  pink_state; int /*<<< orphan*/  pink_need; scalar_t__ pink_pos; } ;
typedef  int int32_t ;

/* Variables and functions */
 int PINK_UNIT ; 
 scalar_t__ lcg_next (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void pink_fill(struct wavesynth_context *ws)
{
    int32_t vt[7] = { 0 }, v = 0;
    int i, j;

    ws->pink_pos = 0;
    if (!ws->pink_need)
        return;
    for (i = 0; i < PINK_UNIT; i++) {
        for (j = 0; j < 7; j++) {
            if ((i >> j) & 1)
                break;
            v -= vt[j];
            vt[j] = (int32_t)lcg_next(&ws->pink_state) >> 3;
            v += vt[j];
        }
        ws->pink_pool[i] = v + ((int32_t)lcg_next(&ws->pink_state) >> 3);
    }
    lcg_next(&ws->pink_state); /* so we use exactly 256 steps */
}