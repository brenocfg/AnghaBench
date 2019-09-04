#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {double* channel_values; scalar_t__ nb_in_channels; } ;
typedef  TYPE_1__ EvalContext ;

/* Variables and functions */
 size_t FFMIN (int,scalar_t__) ; 

__attribute__((used)) static double val(void *priv, double ch)
{
    EvalContext *eval = priv;
    return eval->channel_values[FFMIN((int)ch, eval->nb_in_channels-1)];
}