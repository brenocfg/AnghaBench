#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int int16_t ;
struct TYPE_4__ {int high; int low; int value; } ;
typedef  TYPE_1__ ArithCoder ;

/* Variables and functions */
 int arith2_get_scaled_value (int,int,int) ; 
 int /*<<< orphan*/  arith2_rescale_interval (TYPE_1__*,int,int,int,int) ; 
 int av_log2 (int) ; 

__attribute__((used)) static int arith2_get_prob(ArithCoder *c, int16_t *probs)
{
    int range = c->high - c->low + 1, n = *probs;
    int scale = av_log2(range) - av_log2(n);
    int i     = 0, val;

    if (n << scale > range)
        scale--;

    n <<= scale;

    val = arith2_get_scaled_value(c->value - c->low, n, range) >> scale;
    while (probs[++i] > val) ;

    arith2_rescale_interval(c, range,
                            probs[i] << scale, probs[i - 1] << scale, n);

    return i;
}