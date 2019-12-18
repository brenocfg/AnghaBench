#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int operands_num; TYPE_1__* operands; } ;
struct TYPE_6__ {int height; int width; int channels; int /*<<< orphan*/  dt; } ;
struct TYPE_5__ {scalar_t__ type; int* dims; int /*<<< orphan*/  data_type; int /*<<< orphan*/  name; } ;
typedef  TYPE_1__ DnnOperand ;
typedef  int /*<<< orphan*/  DNNReturnType ;
typedef  TYPE_2__ DNNData ;
typedef  TYPE_3__ ConvolutionalNetwork ;

/* Variables and functions */
 int /*<<< orphan*/  DNN_ERROR ; 
 int /*<<< orphan*/  DNN_SUCCESS ; 
 scalar_t__ DOT_INPUT ; 
 int /*<<< orphan*/  av_assert0 (int) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char const*) ; 

__attribute__((used)) static DNNReturnType get_input_native(void *model, DNNData *input, const char *input_name)
{
    ConvolutionalNetwork *network = (ConvolutionalNetwork *)model;

    for (int i = 0; i < network->operands_num; ++i) {
        DnnOperand *oprd = &network->operands[i];
        if (strcmp(oprd->name, input_name) == 0) {
            if (oprd->type != DOT_INPUT)
                return DNN_ERROR;
            input->dt = oprd->data_type;
            av_assert0(oprd->dims[0] == 1);
            input->height = oprd->dims[1];
            input->width = oprd->dims[2];
            input->channels = oprd->dims[3];
            return DNN_SUCCESS;
        }
    }

    // do not find the input operand
    return DNN_ERROR;
}