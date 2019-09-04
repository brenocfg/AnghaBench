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
struct TYPE_8__ {int input; int delta; int /*<<< orphan*/  train; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_1__ network ;
struct TYPE_9__ {int steps; int inputs; int batch; int output; int outputs; int cell_cpu; int delta; int prev_cell_cpu; int c_cpu; int prev_state_cpu; int h_cpu; int dh_cpu; int f_cpu; int i_cpu; int g_cpu; int o_cpu; int temp3_cpu; int temp_cpu; int temp2_cpu; int dc_cpu; struct TYPE_9__* uo; struct TYPE_9__* ug; struct TYPE_9__* ui; struct TYPE_9__* uf; struct TYPE_9__* wo; struct TYPE_9__* wg; struct TYPE_9__* wi; struct TYPE_9__* wf; } ;
typedef  TYPE_2__ layer ;

/* Variables and functions */
 int /*<<< orphan*/  LOGISTIC ; 
 int /*<<< orphan*/  TANH ; 
 int /*<<< orphan*/  activate_array (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  axpy_cpu (int,int,int,int,int,int) ; 
 int /*<<< orphan*/  backward_connected_layer (TYPE_2__,TYPE_1__) ; 
 int /*<<< orphan*/  copy_cpu (int,int,int,int,int) ; 
 int /*<<< orphan*/  gradient_array (int,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  increment_layer (TYPE_2__*,int) ; 
 int /*<<< orphan*/  mul_cpu (int,int,int,int,int) ; 

void backward_lstm_layer(layer l, network state)
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

    increment_layer(&wf, l.steps - 1);
    increment_layer(&wi, l.steps - 1);
    increment_layer(&wg, l.steps - 1);
    increment_layer(&wo, l.steps - 1);

    increment_layer(&uf, l.steps - 1);
    increment_layer(&ui, l.steps - 1);
    increment_layer(&ug, l.steps - 1);
    increment_layer(&uo, l.steps - 1);

    state.input += l.inputs*l.batch*(l.steps - 1);
    if (state.delta) state.delta += l.inputs*l.batch*(l.steps - 1);

    l.output += l.outputs*l.batch*(l.steps - 1);
    l.cell_cpu += l.outputs*l.batch*(l.steps - 1);
    l.delta += l.outputs*l.batch*(l.steps - 1);

    for (i = l.steps - 1; i >= 0; --i) {
        if (i != 0) copy_cpu(l.outputs*l.batch, l.cell_cpu - l.outputs*l.batch, 1, l.prev_cell_cpu, 1);
        copy_cpu(l.outputs*l.batch, l.cell_cpu, 1, l.c_cpu, 1);
        if (i != 0) copy_cpu(l.outputs*l.batch, l.output - l.outputs*l.batch, 1, l.prev_state_cpu, 1);
        copy_cpu(l.outputs*l.batch, l.output, 1, l.h_cpu, 1);

        l.dh_cpu = (i == 0) ? 0 : l.delta - l.outputs*l.batch;

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

        copy_cpu(l.outputs*l.batch, l.delta, 1, l.temp3_cpu, 1);		

        copy_cpu(l.outputs*l.batch, l.c_cpu, 1, l.temp_cpu, 1);			
        activate_array(l.temp_cpu, l.outputs*l.batch, TANH);			

        copy_cpu(l.outputs*l.batch, l.temp3_cpu, 1, l.temp2_cpu, 1);		
        mul_cpu(l.outputs*l.batch, l.o_cpu, 1, l.temp2_cpu, 1);			

        gradient_array(l.temp_cpu, l.outputs*l.batch, TANH, l.temp2_cpu);
        axpy_cpu(l.outputs*l.batch, 1, l.dc_cpu, 1, l.temp2_cpu, 1);		

        copy_cpu(l.outputs*l.batch, l.c_cpu, 1, l.temp_cpu, 1);			
        activate_array(l.temp_cpu, l.outputs*l.batch, TANH);			
        mul_cpu(l.outputs*l.batch, l.temp3_cpu, 1, l.temp_cpu, 1);		
        gradient_array(l.o_cpu, l.outputs*l.batch, LOGISTIC, l.temp_cpu);
        copy_cpu(l.outputs*l.batch, l.temp_cpu, 1, wo.delta, 1);
        s.input = l.prev_state_cpu;
        s.delta = l.dh_cpu;															
        backward_connected_layer(wo, s);	

        copy_cpu(l.outputs*l.batch, l.temp_cpu, 1, uo.delta, 1);
        s.input = state.input;
        s.delta = state.delta;
        backward_connected_layer(uo, s);									

        copy_cpu(l.outputs*l.batch, l.temp2_cpu, 1, l.temp_cpu, 1);			
        mul_cpu(l.outputs*l.batch, l.i_cpu, 1, l.temp_cpu, 1);				
        gradient_array(l.g_cpu, l.outputs*l.batch, TANH, l.temp_cpu);		
        copy_cpu(l.outputs*l.batch, l.temp_cpu, 1, wg.delta, 1);
        s.input = l.prev_state_cpu;
        s.delta = l.dh_cpu;														
        backward_connected_layer(wg, s);	

        copy_cpu(l.outputs*l.batch, l.temp_cpu, 1, ug.delta, 1);
        s.input = state.input;
        s.delta = state.delta;
        backward_connected_layer(ug, s);																

        copy_cpu(l.outputs*l.batch, l.temp2_cpu, 1, l.temp_cpu, 1);			
        mul_cpu(l.outputs*l.batch, l.g_cpu, 1, l.temp_cpu, 1);				
        gradient_array(l.i_cpu, l.outputs*l.batch, LOGISTIC, l.temp_cpu);	
        copy_cpu(l.outputs*l.batch, l.temp_cpu, 1, wi.delta, 1);
        s.input = l.prev_state_cpu;
        s.delta = l.dh_cpu;
        backward_connected_layer(wi, s);						

        copy_cpu(l.outputs*l.batch, l.temp_cpu, 1, ui.delta, 1);
        s.input = state.input;
        s.delta = state.delta;
        backward_connected_layer(ui, s);									

        copy_cpu(l.outputs*l.batch, l.temp2_cpu, 1, l.temp_cpu, 1);		
        mul_cpu(l.outputs*l.batch, l.prev_cell_cpu, 1, l.temp_cpu, 1);
        gradient_array(l.f_cpu, l.outputs*l.batch, LOGISTIC, l.temp_cpu);
        copy_cpu(l.outputs*l.batch, l.temp_cpu, 1, wf.delta, 1);
        s.input = l.prev_state_cpu;
        s.delta = l.dh_cpu;
        backward_connected_layer(wf, s);						

        copy_cpu(l.outputs*l.batch, l.temp_cpu, 1, uf.delta, 1);
        s.input = state.input;
        s.delta = state.delta;
        backward_connected_layer(uf, s);									

        copy_cpu(l.outputs*l.batch, l.temp2_cpu, 1, l.temp_cpu, 1);			
        mul_cpu(l.outputs*l.batch, l.f_cpu, 1, l.temp_cpu, 1);				
        copy_cpu(l.outputs*l.batch, l.temp_cpu, 1, l.dc_cpu, 1);				

        state.input -= l.inputs*l.batch;
        if (state.delta) state.delta -= l.inputs*l.batch;
        l.output -= l.outputs*l.batch;
        l.cell_cpu -= l.outputs*l.batch;
        l.delta -= l.outputs*l.batch;

        increment_layer(&wf, -1);
        increment_layer(&wi, -1);
        increment_layer(&wg, -1);
        increment_layer(&wo, -1);

        increment_layer(&uf, -1);
        increment_layer(&ui, -1);
        increment_layer(&ug, -1);
        increment_layer(&uo, -1);
    }
}