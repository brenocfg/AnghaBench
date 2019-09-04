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
struct TYPE_5__ {int /*<<< orphan*/  delta; } ;
typedef  TYPE_1__ network ;
struct TYPE_6__ {int w; int h; int c; int batch; int /*<<< orphan*/  delta; int /*<<< orphan*/  norms; int /*<<< orphan*/  beta; } ;
typedef  TYPE_2__ layer ;

/* Variables and functions */
 int /*<<< orphan*/  mul_cpu (int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pow_cpu (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int) ; 

void backward_normalization_layer(const layer layer, network net)
{
    // TODO This is approximate ;-)
    // Also this should add in to delta instead of overwritting.

    int w = layer.w;
    int h = layer.h;
    int c = layer.c;
    pow_cpu(w*h*c*layer.batch, -layer.beta, layer.norms, 1, net.delta, 1);
    mul_cpu(w*h*c*layer.batch, layer.delta, 1, net.delta, 1);
}