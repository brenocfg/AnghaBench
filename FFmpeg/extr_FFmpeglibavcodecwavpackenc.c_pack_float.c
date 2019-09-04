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
typedef  int /*<<< orphan*/  int32_t ;
struct TYPE_4__ {int flags; } ;
typedef  TYPE_1__ WavPackEncodeContext ;

/* Variables and functions */
 int WV_MONO_DATA ; 
 int /*<<< orphan*/  pack_float_sample (TYPE_1__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void pack_float(WavPackEncodeContext *s,
                       int32_t *samples_l, int32_t *samples_r,
                       int nb_samples)
{
    int i;

    if (s->flags & WV_MONO_DATA) {
        for (i = 0; i < nb_samples; i++)
            pack_float_sample(s, &samples_l[i]);
    } else {
        for (i = 0; i < nb_samples; i++) {
            pack_float_sample(s, &samples_l[i]);
            pack_float_sample(s, &samples_r[i]);
        }
    }
}