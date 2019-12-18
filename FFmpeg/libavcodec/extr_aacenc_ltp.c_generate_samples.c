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
struct TYPE_3__ {int lag; float coef; scalar_t__ present; } ;
typedef  TYPE_1__ LongTermPrediction ;

/* Variables and functions */
 int /*<<< orphan*/  memset (float*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void generate_samples(float *buf, LongTermPrediction *ltp)
{
    int i, samples_num = 2048;
    if (!ltp->lag) {
        ltp->present = 0;
        return;
    } else if (ltp->lag < 1024) {
        samples_num = ltp->lag + 1024;
    }
    for (i = 0; i < samples_num; i++)
        buf[i] = ltp->coef*buf[i + 2048 - ltp->lag];
    memset(&buf[i], 0, (2048 - i)*sizeof(float));
}