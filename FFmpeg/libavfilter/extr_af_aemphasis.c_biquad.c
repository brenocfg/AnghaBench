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
struct TYPE_3__ {double w1; double b1; double w2; double b2; double a0; double a1; double a2; } ;
typedef  TYPE_1__ BiquadD2 ;

/* Variables and functions */

__attribute__((used)) static inline double biquad(BiquadD2 *bq, double in)
{
    double n = in;
    double tmp = n - bq->w1 * bq->b1 - bq->w2 * bq->b2;
    double out = tmp * bq->a0 + bq->w1 * bq->a1 + bq->w2 * bq->a2;

    bq->w2 = bq->w1;
    bq->w1 = tmp;

    return out;
}