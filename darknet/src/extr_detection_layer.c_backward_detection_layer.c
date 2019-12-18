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
struct TYPE_6__ {int batch; int inputs; int /*<<< orphan*/  delta; } ;
typedef  TYPE_2__ detection_layer ;

/* Variables and functions */
 int /*<<< orphan*/  axpy_cpu (int,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int) ; 

void backward_detection_layer(const detection_layer l, network net)
{
    axpy_cpu(l.batch*l.inputs, 1, l.delta, 1, net.delta, 1);
}