#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int coil0; int coil2; int coil4; int coil6; int coil7; } ;
struct TYPE_7__ {int discrete_input1; int discrete_input3; int discrete_input5; int discrete_input7; } ;
struct TYPE_6__ {double data_chan0; double data_chan1; double data_chan2; double data_chan3; } ;
struct TYPE_5__ {double data_chan0; double data_chan1; double data_chan2; double data_chan3; } ;

/* Variables and functions */
 TYPE_4__ coil_reg_params ; 
 TYPE_3__ discrete_reg_params ; 
 TYPE_2__ holding_reg_params ; 
 TYPE_1__ input_reg_params ; 

__attribute__((used)) static void setup_reg_data(void)
{
    // Define initial state of parameters
    discrete_reg_params.discrete_input1 = 1;
    discrete_reg_params.discrete_input3 = 1;
    discrete_reg_params.discrete_input5 = 1;
    discrete_reg_params.discrete_input7 = 1;

    holding_reg_params.data_chan0 = 1.34;
    holding_reg_params.data_chan1 = 2.56;
    holding_reg_params.data_chan2 = 3.78;
    holding_reg_params.data_chan3 = 4.90;

    coil_reg_params.coil0 = 1;
    coil_reg_params.coil2 = 1;
    coil_reg_params.coil4 = 1;
    coil_reg_params.coil6 = 1;
    coil_reg_params.coil7 = 1;

    input_reg_params.data_chan0 = 1.34;
    input_reg_params.data_chan1 = 2.56;
    input_reg_params.data_chan2 = 3.78;
    input_reg_params.data_chan3 = 4.90;
}