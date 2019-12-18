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
typedef  scalar_t__ uint32_t ;
struct TYPE_3__ {scalar_t__ param_offset; int mb_param_type; scalar_t__ param_size; } ;
typedef  TYPE_1__ mb_parameter_descriptor_t ;

/* Variables and functions */
#define  MB_PARAM_COIL 131 
#define  MB_PARAM_DISCRETE 130 
#define  MB_PARAM_HOLDING 129 
#define  MB_PARAM_INPUT 128 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  coil_reg_params ; 
 int /*<<< orphan*/  discrete_reg_params ; 
 int /*<<< orphan*/  holding_reg_params ; 
 int /*<<< orphan*/  input_reg_params ; 
 void* malloc (size_t) ; 

__attribute__((used)) static void* sense_modbus_get_param_data(const mb_parameter_descriptor_t* param_descriptor)
{
    assert(param_descriptor != NULL);
    void* instance_ptr = NULL;
    if (param_descriptor->param_offset != 0) {
       switch(param_descriptor->mb_param_type)
       {
           case MB_PARAM_HOLDING:
               instance_ptr = (void*)((uint32_t)&holding_reg_params + param_descriptor->param_offset - 1);
               break;
           case MB_PARAM_INPUT:
               instance_ptr = (void*)((uint32_t)&input_reg_params + param_descriptor->param_offset - 1);
               break;
           case MB_PARAM_COIL:
               instance_ptr = (void*)((uint32_t)&coil_reg_params + param_descriptor->param_offset - 1);
               break;
           case MB_PARAM_DISCRETE:
               instance_ptr = (void*)((uint32_t)&discrete_reg_params + param_descriptor->param_offset - 1);
               break;
           default:
               instance_ptr = NULL;
               break;
       }
    } else {
        instance_ptr = malloc((size_t)(param_descriptor->param_size));;
    }
    return instance_ptr;
}