#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_7__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint32_t ;
typedef  size_t int32_t ;
struct TYPE_15__ {int /*<<< orphan*/  (* pf_exec ) (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
struct TYPE_14__ {scalar_t__ layers_num; scalar_t__ operands_num; size_t* output_indexes; TYPE_2__* operands; TYPE_1__* layers; int /*<<< orphan*/  nb_output; } ;
struct TYPE_13__ {int /*<<< orphan*/  dt; int /*<<< orphan*/  channels; int /*<<< orphan*/  width; int /*<<< orphan*/  height; int /*<<< orphan*/  data; } ;
struct TYPE_12__ {scalar_t__ model; } ;
struct TYPE_11__ {int /*<<< orphan*/  data_type; int /*<<< orphan*/ * dims; int /*<<< orphan*/  data; } ;
struct TYPE_10__ {size_t type; int /*<<< orphan*/  params; int /*<<< orphan*/  output_operand_index; int /*<<< orphan*/  input_operand_indexes; } ;
typedef  TYPE_2__ DnnOperand ;
typedef  int /*<<< orphan*/  DNNReturnType ;
typedef  TYPE_3__ DNNModel ;
typedef  size_t DNNLayerType ;
typedef  TYPE_4__ DNNData ;
typedef  TYPE_5__ ConvolutionalNetwork ;

/* Variables and functions */
 int /*<<< orphan*/  DNN_ERROR ; 
 int /*<<< orphan*/  DNN_SUCCESS ; 
 size_t FFMIN (size_t,int /*<<< orphan*/ ) ; 
 TYPE_7__* layer_funcs ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

DNNReturnType ff_dnn_execute_model_native(const DNNModel *model, DNNData *outputs, uint32_t nb_output)
{
    ConvolutionalNetwork *network = (ConvolutionalNetwork *)model->model;
    int32_t layer;
    uint32_t nb = FFMIN(nb_output, network->nb_output);

    if (network->layers_num <= 0 || network->operands_num <= 0)
        return DNN_ERROR;
    if (!network->operands[0].data)
        return DNN_ERROR;

    for (layer = 0; layer < network->layers_num; ++layer){
        DNNLayerType layer_type = network->layers[layer].type;
        layer_funcs[layer_type].pf_exec(network->operands,
                                  network->layers[layer].input_operand_indexes,
                                  network->layers[layer].output_operand_index,
                                  network->layers[layer].params);
    }

    for (uint32_t i = 0; i < nb; ++i) {
        DnnOperand *oprd = &network->operands[network->output_indexes[i]];
        outputs[i].data = oprd->data;
        outputs[i].height = oprd->dims[1];
        outputs[i].width = oprd->dims[2];
        outputs[i].channels = oprd->dims[3];
        outputs[i].dt = oprd->data_type;
    }

    return DNN_SUCCESS;
}