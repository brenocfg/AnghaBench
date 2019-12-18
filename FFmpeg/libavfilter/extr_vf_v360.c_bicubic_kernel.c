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
 int /*<<< orphan*/  calculate_bicubic_coeffs (float,float*) ; 
 int /*<<< orphan*/  lrintf (float) ; 

__attribute__((used)) static void bicubic_kernel(float du, float dv, const XYRemap *rmap,
                           uint16_t *u, uint16_t *v, int16_t *ker)
{
    float du_coeffs[4];
    float dv_coeffs[4];

    calculate_bicubic_coeffs(du, du_coeffs);
    calculate_bicubic_coeffs(dv, dv_coeffs);

    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            u[i * 4 + j] = rmap->u[i][j];
            v[i * 4 + j] = rmap->v[i][j];
            ker[i * 4 + j] = lrintf(du_coeffs[j] * dv_coeffs[i] * 16385.f);
        }
    }
}