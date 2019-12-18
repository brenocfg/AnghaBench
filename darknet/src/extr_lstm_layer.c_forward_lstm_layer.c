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
struct TYPE_8__ {int input; scalar_t__ train; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_1__ network ;
struct TYPE_9__ {int outputs; int batch; int steps; int h_cpu; int output; int f_cpu; int i_cpu; int g_cpu; int o_cpu; int temp_cpu; int c_cpu; int cell_cpu; int inputs; int /*<<< orphan*/  delta; struct TYPE_9__* uo; struct TYPE_9__* ug; struct TYPE_9__* ui; struct TYPE_9__* uf; struct TYPE_9__* wo; struct TYPE_9__* wg; struct TYPE_9__* wi; struct TYPE_9__* wf; } ;
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

void forward_lstm_layer(layer l, network state)
{
    network s = { 0 };
    s.train = state.train;
    int i;
    layer wf = *(l.wf);
    layer wi = *(l.wi);
    layer wg = *(l.wg);
    layer wo = *(l.wo);

    layer uf = *(l.uf);
    layer ui = *(l.ui);
    layer ug = *(l.ug);
    layer uo = *(l.uo);

    fill_cpu(l.outputs * l.batch * l.steps, 0, wf.delta, 1);
    fill_cpu(l.outputs * l.batch * l.steps, 0, wi.delta, 1);
    fill_cpu(l.outputs * l.batch * l.steps, 0, wg.delta, 1);
    fill_cpu(l.outputs * l.batch * l.steps, 0, wo.delta, 1);

    fill_cpu(l.outputs * l.batch * l.steps, 0, uf.delta, 1);
    fill_cpu(l.outputs * l.batch * l.steps, 0, ui.delta, 1);
    fill_cpu(l.outputs * l.batch * l.steps, 0, ug.delta, 1);
    fill_cpu(l.outputs * l.batch * l.steps, 0, uo.delta, 1);
    if (state.train) {
        fill_cpu(l.outputs * l.batch * l.steps, 0, l.delta, 1);
    }

    for (i = 0; i < l.steps; ++i) {
        s.input = l.h_cpu;
        forward_connected_layer(wf, s);							
        forward_connected_layer(wi, s);							
        forward_connected_layer(wg, s);							
        forward_connected_layer(wo, s);							

        s.input = state.input;
        forward_connected_layer(uf, s);							
        forward_connected_layer(ui, s);							
        forward_connected_layer(ug, s);							
        forward_connected_layer(uo, s);							

        copy_cpu(l.outputs*l.batch, wf.output, 1, l.f_cpu, 1);
        axpy_cpu(l.outputs*l.batch, 1, uf.output, 1, l.f_cpu, 1);

        copy_cpu(l.outputs*l.batch, wi.output, 1, l.i_cpu, 1);	
        axpy_cpu(l.outputs*l.batch, 1, ui.output, 1, l.i_cpu, 1);	

        copy_cpu(l.outputs*l.batch, wg.output, 1, l.g_cpu, 1);	
        axpy_cpu(l.outputs*l.batch, 1, ug.output, 1, l.g_cpu, 1);	

        copy_cpu(l.outputs*l.batch, wo.output, 1, l.o_cpu, 1);	
        axpy_cpu(l.outputs*l.batch, 1, uo.output, 1, l.o_cpu, 1);	

        activate_array(l.f_cpu, l.outputs*l.batch, LOGISTIC);		
        activate_array(l.i_cpu, l.outputs*l.batch, LOGISTIC);		
        activate_array(l.g_cpu, l.outputs*l.batch, TANH);			
        activate_array(l.o_cpu, l.outputs*l.batch, LOGISTIC);		

        copy_cpu(l.outputs*l.batch, l.i_cpu, 1, l.temp_cpu, 1);		
        mul_cpu(l.outputs*l.batch, l.g_cpu, 1, l.temp_cpu, 1);		
        mul_cpu(l.outputs*l.batch, l.f_cpu, 1, l.c_cpu, 1);			
        axpy_cpu(l.outputs*l.batch, 1, l.temp_cpu, 1, l.c_cpu, 1);	

        copy_cpu(l.outputs*l.batch, l.c_cpu, 1, l.h_cpu, 1);			
        activate_array(l.h_cpu, l.outputs*l.batch, TANH);		
        mul_cpu(l.outputs*l.batch, l.o_cpu, 1, l.h_cpu, 1);	

        copy_cpu(l.outputs*l.batch, l.c_cpu, 1, l.cell_cpu, 1);		
        copy_cpu(l.outputs*l.batch, l.h_cpu, 1, l.output, 1);

        state.input += l.inputs*l.batch;
        l.output    += l.outputs*l.batch;
        l.cell_cpu      += l.outputs*l.batch;

        increment_layer(&wf, 1);
        increment_layer(&wi, 1);
        increment_layer(&wg, 1);
        increment_layer(&wo, 1);

        increment_layer(&uf, 1);
        increment_layer(&ui, 1);
        increment_layer(&ug, 1);
        increment_layer(&uo, 1);
    }
}