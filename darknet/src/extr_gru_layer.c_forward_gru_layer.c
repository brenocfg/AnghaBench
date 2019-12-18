#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int input; scalar_t__ train; } ;
typedef  TYPE_1__ network ;
struct TYPE_9__ {int outputs; int batch; int steps; int state; int prev_state; int output; int z_cpu; int r_cpu; int forgot_state; int h_cpu; int inputs; scalar_t__ tanh; int /*<<< orphan*/  delta; struct TYPE_9__* wh; struct TYPE_9__* wr; struct TYPE_9__* wz; struct TYPE_9__* uh; struct TYPE_9__* ur; struct TYPE_9__* uz; } ;
typedef  TYPE_2__ layer ;

/* Variables and functions */
 int /*<<< orphan*/  LOGISTIC ; 
 int /*<<< orphan*/  TANH ; 
 int /*<<< orphan*/  activate_array (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  axpy_cpu (int,int,int,int,int,int) ; 
 int /*<<< orphan*/  copy_cpu (int,int,int,int,int) ; 
 int /*<<< orphan*/  fill_cpu (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  forward_connected_layer (TYPE_2__,TYPE_1__) ; 
 int /*<<< orphan*/  increment_layer (TYPE_2__*,int) ; 
 int /*<<< orphan*/  mul_cpu (int,int,int,int,int) ; 
 int /*<<< orphan*/  weighted_sum_cpu (int,int,int,int,int) ; 

void forward_gru_layer(layer l, network net)
{
    network s = net;
    s.train = net.train;
    int i;
    layer uz = *(l.uz);
    layer ur = *(l.ur);
    layer uh = *(l.uh);

    layer wz = *(l.wz);
    layer wr = *(l.wr);
    layer wh = *(l.wh);

    fill_cpu(l.outputs * l.batch * l.steps, 0, uz.delta, 1);
    fill_cpu(l.outputs * l.batch * l.steps, 0, ur.delta, 1);
    fill_cpu(l.outputs * l.batch * l.steps, 0, uh.delta, 1);

    fill_cpu(l.outputs * l.batch * l.steps, 0, wz.delta, 1);
    fill_cpu(l.outputs * l.batch * l.steps, 0, wr.delta, 1);
    fill_cpu(l.outputs * l.batch * l.steps, 0, wh.delta, 1);
    if(net.train) {
        fill_cpu(l.outputs * l.batch * l.steps, 0, l.delta, 1);
        copy_cpu(l.outputs*l.batch, l.state, 1, l.prev_state, 1);
    }

    for (i = 0; i < l.steps; ++i) {
        s.input = l.state;
        forward_connected_layer(wz, s);
        forward_connected_layer(wr, s);

        s.input = net.input;
        forward_connected_layer(uz, s);
        forward_connected_layer(ur, s);
        forward_connected_layer(uh, s);


        copy_cpu(l.outputs*l.batch, uz.output, 1, l.z_cpu, 1);
        axpy_cpu(l.outputs*l.batch, 1, wz.output, 1, l.z_cpu, 1);

        copy_cpu(l.outputs*l.batch, ur.output, 1, l.r_cpu, 1);
        axpy_cpu(l.outputs*l.batch, 1, wr.output, 1, l.r_cpu, 1);

        activate_array(l.z_cpu, l.outputs*l.batch, LOGISTIC);
        activate_array(l.r_cpu, l.outputs*l.batch, LOGISTIC);

        copy_cpu(l.outputs*l.batch, l.state, 1, l.forgot_state, 1);
        mul_cpu(l.outputs*l.batch, l.r_cpu, 1, l.forgot_state, 1);

        s.input = l.forgot_state;
        forward_connected_layer(wh, s);

        copy_cpu(l.outputs*l.batch, uh.output, 1, l.h_cpu, 1);
        axpy_cpu(l.outputs*l.batch, 1, wh.output, 1, l.h_cpu, 1);

        if(l.tanh){
            activate_array(l.h_cpu, l.outputs*l.batch, TANH);
        } else {
            activate_array(l.h_cpu, l.outputs*l.batch, LOGISTIC);
        }

        weighted_sum_cpu(l.state, l.h_cpu, l.z_cpu, l.outputs*l.batch, l.output);

        copy_cpu(l.outputs*l.batch, l.output, 1, l.state, 1);

        net.input += l.inputs*l.batch;
        l.output += l.outputs*l.batch;
        increment_layer(&uz, 1);
        increment_layer(&ur, 1);
        increment_layer(&uh, 1);

        increment_layer(&wz, 1);
        increment_layer(&wr, 1);
        increment_layer(&wh, 1);
    }
}