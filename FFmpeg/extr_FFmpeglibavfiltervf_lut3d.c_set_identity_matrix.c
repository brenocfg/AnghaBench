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
struct rgbvec {int r; int g; int b; } ;
struct TYPE_3__ {int lutsize; struct rgbvec*** lut; } ;
typedef  TYPE_1__ LUT3DContext ;

/* Variables and functions */

__attribute__((used)) static void set_identity_matrix(LUT3DContext *lut3d, int size)
{
    int i, j, k;
    const float c = 1. / (size - 1);

    lut3d->lutsize = size;
    for (k = 0; k < size; k++) {
        for (j = 0; j < size; j++) {
            for (i = 0; i < size; i++) {
                struct rgbvec *vec = &lut3d->lut[k][j][i];
                vec->r = k * c;
                vec->g = j * c;
                vec->b = i * c;
            }
        }
    }
}