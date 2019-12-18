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
typedef  struct rgbvec {int /*<<< orphan*/  b; int /*<<< orphan*/  g; int /*<<< orphan*/  r; int /*<<< orphan*/  member_2; int /*<<< orphan*/  member_1; int /*<<< orphan*/  member_0; } const rgbvec ;
struct TYPE_3__ {int lutsize2; int lutsize; struct rgbvec const* lut; } ;
typedef  TYPE_1__ LUT3DContext ;

/* Variables and functions */
 int const NEXT (int /*<<< orphan*/ ) ; 
 int const PREV (int /*<<< orphan*/ ) ; 
 struct rgbvec const lerp (struct rgbvec const*,struct rgbvec const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline struct rgbvec interp_trilinear(const LUT3DContext *lut3d,
                                             const struct rgbvec *s)
{
    const int lutsize2 = lut3d->lutsize2;
    const int lutsize  = lut3d->lutsize;
    const int prev[] = {PREV(s->r), PREV(s->g), PREV(s->b)};
    const int next[] = {NEXT(s->r), NEXT(s->g), NEXT(s->b)};
    const struct rgbvec d = {s->r - prev[0], s->g - prev[1], s->b - prev[2]};
    const struct rgbvec c000 = lut3d->lut[prev[0] * lutsize2 + prev[1] * lutsize + prev[2]];
    const struct rgbvec c001 = lut3d->lut[prev[0] * lutsize2 + prev[1] * lutsize + next[2]];
    const struct rgbvec c010 = lut3d->lut[prev[0] * lutsize2 + next[1] * lutsize + prev[2]];
    const struct rgbvec c011 = lut3d->lut[prev[0] * lutsize2 + next[1] * lutsize + next[2]];
    const struct rgbvec c100 = lut3d->lut[next[0] * lutsize2 + prev[1] * lutsize + prev[2]];
    const struct rgbvec c101 = lut3d->lut[next[0] * lutsize2 + prev[1] * lutsize + next[2]];
    const struct rgbvec c110 = lut3d->lut[next[0] * lutsize2 + next[1] * lutsize + prev[2]];
    const struct rgbvec c111 = lut3d->lut[next[0] * lutsize2 + next[1] * lutsize + next[2]];
    const struct rgbvec c00  = lerp(&c000, &c100, d.r);
    const struct rgbvec c10  = lerp(&c010, &c110, d.r);
    const struct rgbvec c01  = lerp(&c001, &c101, d.r);
    const struct rgbvec c11  = lerp(&c011, &c111, d.r);
    const struct rgbvec c0   = lerp(&c00,  &c10,  d.g);
    const struct rgbvec c1   = lerp(&c01,  &c11,  d.g);
    const struct rgbvec c    = lerp(&c0,   &c1,   d.b);
    return c;
}