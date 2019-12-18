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
 int roundf (float) ; 

__attribute__((used)) static void nearest_kernel(float du, float dv, const XYRemap *rmap,
                           uint16_t *u, uint16_t *v, int16_t *ker)
{
    const int i = roundf(dv) + 1;
    const int j = roundf(du) + 1;

    u[0] = rmap->u[i][j];
    v[0] = rmap->v[i][j];
}