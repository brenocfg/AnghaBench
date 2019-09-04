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
struct rgbvec {int r; int g; int b; int /*<<< orphan*/  member_2; int /*<<< orphan*/  member_1; int /*<<< orphan*/  member_0; } ;
struct TYPE_3__ {struct rgbvec*** lut; } ;
typedef  TYPE_1__ LUT3DContext ;

/* Variables and functions */
 int const NEXT (int) ; 
 int const PREV (int) ; 

__attribute__((used)) static inline struct rgbvec interp_tetrahedral(const LUT3DContext *lut3d,
                                               const struct rgbvec *s)
{
    const int prev[] = {PREV(s->r), PREV(s->g), PREV(s->b)};
    const int next[] = {NEXT(s->r), NEXT(s->g), NEXT(s->b)};
    const struct rgbvec d = {s->r - prev[0], s->g - prev[1], s->b - prev[2]};
    const struct rgbvec c000 = lut3d->lut[prev[0]][prev[1]][prev[2]];
    const struct rgbvec c111 = lut3d->lut[next[0]][next[1]][next[2]];
    struct rgbvec c;
    if (d.r > d.g) {
        if (d.g > d.b) {
            const struct rgbvec c100 = lut3d->lut[next[0]][prev[1]][prev[2]];
            const struct rgbvec c110 = lut3d->lut[next[0]][next[1]][prev[2]];
            c.r = (1-d.r) * c000.r + (d.r-d.g) * c100.r + (d.g-d.b) * c110.r + (d.b) * c111.r;
            c.g = (1-d.r) * c000.g + (d.r-d.g) * c100.g + (d.g-d.b) * c110.g + (d.b) * c111.g;
            c.b = (1-d.r) * c000.b + (d.r-d.g) * c100.b + (d.g-d.b) * c110.b + (d.b) * c111.b;
        } else if (d.r > d.b) {
            const struct rgbvec c100 = lut3d->lut[next[0]][prev[1]][prev[2]];
            const struct rgbvec c101 = lut3d->lut[next[0]][prev[1]][next[2]];
            c.r = (1-d.r) * c000.r + (d.r-d.b) * c100.r + (d.b-d.g) * c101.r + (d.g) * c111.r;
            c.g = (1-d.r) * c000.g + (d.r-d.b) * c100.g + (d.b-d.g) * c101.g + (d.g) * c111.g;
            c.b = (1-d.r) * c000.b + (d.r-d.b) * c100.b + (d.b-d.g) * c101.b + (d.g) * c111.b;
        } else {
            const struct rgbvec c001 = lut3d->lut[prev[0]][prev[1]][next[2]];
            const struct rgbvec c101 = lut3d->lut[next[0]][prev[1]][next[2]];
            c.r = (1-d.b) * c000.r + (d.b-d.r) * c001.r + (d.r-d.g) * c101.r + (d.g) * c111.r;
            c.g = (1-d.b) * c000.g + (d.b-d.r) * c001.g + (d.r-d.g) * c101.g + (d.g) * c111.g;
            c.b = (1-d.b) * c000.b + (d.b-d.r) * c001.b + (d.r-d.g) * c101.b + (d.g) * c111.b;
        }
    } else {
        if (d.b > d.g) {
            const struct rgbvec c001 = lut3d->lut[prev[0]][prev[1]][next[2]];
            const struct rgbvec c011 = lut3d->lut[prev[0]][next[1]][next[2]];
            c.r = (1-d.b) * c000.r + (d.b-d.g) * c001.r + (d.g-d.r) * c011.r + (d.r) * c111.r;
            c.g = (1-d.b) * c000.g + (d.b-d.g) * c001.g + (d.g-d.r) * c011.g + (d.r) * c111.g;
            c.b = (1-d.b) * c000.b + (d.b-d.g) * c001.b + (d.g-d.r) * c011.b + (d.r) * c111.b;
        } else if (d.b > d.r) {
            const struct rgbvec c010 = lut3d->lut[prev[0]][next[1]][prev[2]];
            const struct rgbvec c011 = lut3d->lut[prev[0]][next[1]][next[2]];
            c.r = (1-d.g) * c000.r + (d.g-d.b) * c010.r + (d.b-d.r) * c011.r + (d.r) * c111.r;
            c.g = (1-d.g) * c000.g + (d.g-d.b) * c010.g + (d.b-d.r) * c011.g + (d.r) * c111.g;
            c.b = (1-d.g) * c000.b + (d.g-d.b) * c010.b + (d.b-d.r) * c011.b + (d.r) * c111.b;
        } else {
            const struct rgbvec c010 = lut3d->lut[prev[0]][next[1]][prev[2]];
            const struct rgbvec c110 = lut3d->lut[next[0]][next[1]][prev[2]];
            c.r = (1-d.g) * c000.r + (d.g-d.r) * c010.r + (d.r-d.b) * c110.r + (d.b) * c111.r;
            c.g = (1-d.g) * c000.g + (d.g-d.r) * c010.g + (d.r-d.b) * c110.g + (d.b) * c111.g;
            c.b = (1-d.g) * c000.b + (d.g-d.r) * c010.b + (d.r-d.b) * c110.b + (d.b) * c111.b;
        }
    }
    return c;
}