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
struct rgbvec {int /*<<< orphan*/  b; int /*<<< orphan*/  g; int /*<<< orphan*/  r; } ;
struct TYPE_3__ {size_t lutsize2; size_t lutsize; struct rgbvec* lut; } ;
typedef  TYPE_1__ LUT3DContext ;

/* Variables and functions */
 size_t NEAR (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline struct rgbvec interp_nearest(const LUT3DContext *lut3d,
                                           const struct rgbvec *s)
{
    return lut3d->lut[NEAR(s->r) * lut3d->lutsize2 + NEAR(s->g) * lut3d->lutsize + NEAR(s->b)];
}