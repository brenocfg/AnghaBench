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
typedef  int /*<<< orphan*/  uint16_t ;
typedef  int /*<<< orphan*/  int16_t ;
struct TYPE_3__ {int /*<<< orphan*/ ** v; int /*<<< orphan*/ ** u; } ;
typedef  TYPE_1__ XYRemap ;

/* Variables and functions */
 int /*<<< orphan*/  lrintf (float) ; 

__attribute__((used)) static void bilinear_kernel(float du, float dv, const XYRemap *rmap,
                            uint16_t *u, uint16_t *v, int16_t *ker)
{
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            u[i * 2 + j] = rmap->u[i + 1][j + 1];
            v[i * 2 + j] = rmap->v[i + 1][j + 1];
        }
    }

    ker[0] = lrintf((1.f - du) * (1.f - dv) * 16385.f);
    ker[1] = lrintf(       du  * (1.f - dv) * 16385.f);
    ker[2] = lrintf((1.f - du) *        dv  * 16385.f);
    ker[3] = lrintf(       du  *        dv  * 16385.f);
}