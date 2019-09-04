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
typedef  int /*<<< orphan*/  ptrdiff_t ;
typedef  scalar_t__ int16_t ;

/* Variables and functions */
 int /*<<< orphan*/  memset (scalar_t__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void lowpass_prediction(int16_t *dst, int16_t *pred,
                               int width, int height, ptrdiff_t stride)
{
    int16_t val;
    int i, j;

    memset(pred, 0, width * sizeof(*pred));

    for (i = 0; i < height; i++) {
        val    = pred[0] + dst[0];
        dst[0] = pred[0] = val;
        for (j = 1; j < width; j++) {
            val     = pred[j] + dst[j];
            dst[j]  = pred[j] = val;
            dst[j] += dst[j-1];
        }
        dst += stride;
    }
}