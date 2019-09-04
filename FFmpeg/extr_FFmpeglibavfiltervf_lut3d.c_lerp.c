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
struct rgbvec {int /*<<< orphan*/  member_2; int /*<<< orphan*/  b; int /*<<< orphan*/  member_1; int /*<<< orphan*/  g; int /*<<< orphan*/  member_0; int /*<<< orphan*/  r; } ;

/* Variables and functions */
 int /*<<< orphan*/  lerpf (int /*<<< orphan*/ ,int /*<<< orphan*/ ,float) ; 

__attribute__((used)) static inline struct rgbvec lerp(const struct rgbvec *v0, const struct rgbvec *v1, float f)
{
    struct rgbvec v = {
        lerpf(v0->r, v1->r, f), lerpf(v0->g, v1->g, f), lerpf(v0->b, v1->b, f)
    };
    return v;
}