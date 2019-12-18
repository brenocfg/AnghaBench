#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct rgbvec {int r; int g; int b; } ;
struct TYPE_6__ {TYPE_1__* priv; } ;
struct TYPE_5__ {struct rgbvec* lut; } ;
typedef  TYPE_1__ LUT3DContext ;
typedef  TYPE_2__ AVFilterContext ;

/* Variables and functions */
 int allocate_3dlut (TYPE_2__*,int) ; 

__attribute__((used)) static int set_identity_matrix(AVFilterContext *ctx, int size)
{
    LUT3DContext *lut3d = ctx->priv;
    int ret, i, j, k;
    const int size2 = size * size;
    const float c = 1. / (size - 1);

    ret = allocate_3dlut(ctx, size);
    if (ret < 0)
        return ret;

    for (k = 0; k < size; k++) {
        for (j = 0; j < size; j++) {
            for (i = 0; i < size; i++) {
                struct rgbvec *vec = &lut3d->lut[k * size2 + j * size + i];
                vec->r = k * c;
                vec->g = j * c;
                vec->b = i * c;
            }
        }
    }

    return 0;
}