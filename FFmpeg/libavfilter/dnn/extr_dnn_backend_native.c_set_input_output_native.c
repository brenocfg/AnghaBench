#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint32_t ;
struct TYPE_8__ {scalar_t__ layers_num; scalar_t__ operands_num; size_t nb_output; int* output_indexes; TYPE_1__* operands; } ;
struct TYPE_7__ {int height; int width; int channels; int* data; } ;
struct TYPE_6__ {scalar_t__ type; int* dims; int* data; int /*<<< orphan*/  name; int /*<<< orphan*/  length; } ;
typedef  TYPE_1__ DnnOperand ;
typedef  int /*<<< orphan*/  DNNReturnType ;
typedef  TYPE_2__ DNNData ;
typedef  TYPE_3__ ConvolutionalNetwork ;

/* Variables and functions */
 int /*<<< orphan*/  DNN_ERROR ; 
 int /*<<< orphan*/  DNN_SUCCESS ; 
 scalar_t__ DOT_INPUT ; 
 int /*<<< orphan*/  av_freep (int**) ; 
 int* av_malloc (int /*<<< orphan*/ ) ; 
 int* av_mallocz_array (size_t,int) ; 
 int /*<<< orphan*/  calculate_operand_data_length (TYPE_1__*) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char const*) ; 

__attribute__((used)) static DNNReturnType set_input_output_native(void *model, DNNData *input, const char *input_name, const char **output_names, uint32_t nb_output)
{
    ConvolutionalNetwork *network = (ConvolutionalNetwork *)model;
    DnnOperand *oprd = NULL;

    if (network->layers_num <= 0 || network->operands_num <= 0)
        return DNN_ERROR;

    /* inputs */
    for (int i = 0; i < network->operands_num; ++i) {
        oprd = &network->operands[i];
        if (strcmp(oprd->name, input_name) == 0) {
            if (oprd->type != DOT_INPUT)
                return DNN_ERROR;
            break;
        }
        oprd = NULL;
    }

    if (!oprd)
        return DNN_ERROR;

    oprd->dims[0] = 1;
    oprd->dims[1] = input->height;
    oprd->dims[2] = input->width;
    oprd->dims[3] = input->channels;

    av_freep(&oprd->data);
    oprd->length = calculate_operand_data_length(oprd);
    oprd->data = av_malloc(oprd->length);
    if (!oprd->data)
        return DNN_ERROR;

    input->data = oprd->data;

    /* outputs */
    network->nb_output = 0;
    av_freep(&network->output_indexes);
    network->output_indexes = av_mallocz_array(nb_output, sizeof(*network->output_indexes));
    if (!network->output_indexes)
        return DNN_ERROR;

    for (uint32_t i = 0; i < nb_output; ++i) {
        const char *output_name = output_names[i];
        for (int j = 0; j < network->operands_num; ++j) {
            oprd = &network->operands[j];
            if (strcmp(oprd->name, output_name) == 0) {
                network->output_indexes[network->nb_output++] = j;
                break;
            }
        }
    }

    if (network->nb_output != nb_output)
        return DNN_ERROR;

    return DNN_SUCCESS;
}