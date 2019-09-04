#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int int64_t ;
typedef  int int32_t ;
struct TYPE_9__ {int input_num; int output_num; int kernel_size; int activation; int /*<<< orphan*/  biases; int /*<<< orphan*/  kernel; } ;
struct TYPE_8__ {int /*<<< orphan*/  status; int /*<<< orphan*/  graph; } ;
struct TYPE_7__ {int /*<<< orphan*/ * oper; scalar_t__ index; } ;
typedef  int /*<<< orphan*/  TF_Tensor ;
typedef  TYPE_1__ TF_Output ;
typedef  int /*<<< orphan*/  TF_OperationDescription ;
typedef  int /*<<< orphan*/  TF_Operation ;
typedef  TYPE_2__ TFModel ;
typedef  int /*<<< orphan*/  DNNReturnType ;
typedef  TYPE_3__ ConvolutionalParams ;

/* Variables and functions */
 int /*<<< orphan*/  DNN_ERROR ; 
 int /*<<< orphan*/  DNN_SUCCESS ; 
 int NAME_BUFFER_SIZE ; 
#define  RELU 130 
#define  SIGMOID 129 
#define  TANH 128 
 int /*<<< orphan*/  TF_AddInput (int /*<<< orphan*/ *,TYPE_1__) ; 
 int /*<<< orphan*/ * TF_AllocateTensor (int /*<<< orphan*/ ,int*,int,int) ; 
 int /*<<< orphan*/  TF_FLOAT ; 
 int /*<<< orphan*/ * TF_FinishOperation (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ TF_GetCode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TF_INT32 ; 
 int /*<<< orphan*/ * TF_NewOperation (int /*<<< orphan*/ ,char*,char*) ; 
 scalar_t__ TF_OK ; 
 int /*<<< orphan*/  TF_SetAttrIntList (int /*<<< orphan*/ *,char*,int*,int) ; 
 int /*<<< orphan*/  TF_SetAttrString (int /*<<< orphan*/ *,char*,char*,int) ; 
 int /*<<< orphan*/  TF_SetAttrTensor (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TF_SetAttrType (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TF_TensorData (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int const) ; 

__attribute__((used)) static DNNReturnType add_conv_layer(TFModel *tf_model, TF_Operation *transpose_op, TF_Operation **cur_op,
                                    ConvolutionalParams* params, const int layer)
{
    TF_Operation *op;
    TF_OperationDescription *op_desc;
    TF_Output input;
    int64_t strides[] = {1, 1, 1, 1};
    TF_Tensor *tensor;
    int64_t dims[4];
    int dims_len;
    char name_buffer[NAME_BUFFER_SIZE];
    int32_t size;

    size = params->input_num * params->output_num * params->kernel_size * params->kernel_size;
    input.index = 0;

    snprintf(name_buffer, NAME_BUFFER_SIZE, "conv_kernel%d", layer);
    op_desc = TF_NewOperation(tf_model->graph, "Const", name_buffer);
    TF_SetAttrType(op_desc, "dtype", TF_FLOAT);
    dims[0] = params->output_num;
    dims[1] = params->kernel_size;
    dims[2] = params->kernel_size;
    dims[3] = params->input_num;
    dims_len = 4;
    tensor = TF_AllocateTensor(TF_FLOAT, dims, dims_len, size * sizeof(float));
    memcpy(TF_TensorData(tensor), params->kernel, size * sizeof(float));
    TF_SetAttrTensor(op_desc, "value", tensor, tf_model->status);
    if (TF_GetCode(tf_model->status) != TF_OK){
        return DNN_ERROR;
    }
    op = TF_FinishOperation(op_desc, tf_model->status);
    if (TF_GetCode(tf_model->status) != TF_OK){
        return DNN_ERROR;
    }

    snprintf(name_buffer, NAME_BUFFER_SIZE, "transpose%d", layer);
    op_desc = TF_NewOperation(tf_model->graph, "Transpose", name_buffer);
    input.oper = op;
    TF_AddInput(op_desc, input);
    input.oper = transpose_op;
    TF_AddInput(op_desc, input);
    TF_SetAttrType(op_desc, "T", TF_FLOAT);
    TF_SetAttrType(op_desc, "Tperm", TF_INT32);
    op = TF_FinishOperation(op_desc, tf_model->status);
    if (TF_GetCode(tf_model->status) != TF_OK){
        return DNN_ERROR;
    }

    snprintf(name_buffer, NAME_BUFFER_SIZE, "conv2d%d", layer);
    op_desc = TF_NewOperation(tf_model->graph, "Conv2D", name_buffer);
    input.oper = *cur_op;
    TF_AddInput(op_desc, input);
    input.oper = op;
    TF_AddInput(op_desc, input);
    TF_SetAttrType(op_desc, "T", TF_FLOAT);
    TF_SetAttrIntList(op_desc, "strides", strides, 4);
    TF_SetAttrString(op_desc, "padding", "VALID", 5);
    *cur_op = TF_FinishOperation(op_desc, tf_model->status);
    if (TF_GetCode(tf_model->status) != TF_OK){
        return DNN_ERROR;
    }

    snprintf(name_buffer, NAME_BUFFER_SIZE, "conv_biases%d", layer);
    op_desc = TF_NewOperation(tf_model->graph, "Const", name_buffer);
    TF_SetAttrType(op_desc, "dtype", TF_FLOAT);
    dims[0] = params->output_num;
    dims_len = 1;
    tensor = TF_AllocateTensor(TF_FLOAT, dims, dims_len, params->output_num * sizeof(float));
    memcpy(TF_TensorData(tensor), params->biases, params->output_num * sizeof(float));
    TF_SetAttrTensor(op_desc, "value", tensor, tf_model->status);
    if (TF_GetCode(tf_model->status) != TF_OK){
        return DNN_ERROR;
    }
    op = TF_FinishOperation(op_desc, tf_model->status);
    if (TF_GetCode(tf_model->status) != TF_OK){
        return DNN_ERROR;
    }

    snprintf(name_buffer, NAME_BUFFER_SIZE, "bias_add%d", layer);
    op_desc = TF_NewOperation(tf_model->graph, "BiasAdd", name_buffer);
    input.oper = *cur_op;
    TF_AddInput(op_desc, input);
    input.oper = op;
    TF_AddInput(op_desc, input);
    TF_SetAttrType(op_desc, "T", TF_FLOAT);
    *cur_op = TF_FinishOperation(op_desc, tf_model->status);
    if (TF_GetCode(tf_model->status) != TF_OK){
        return DNN_ERROR;
    }

    snprintf(name_buffer, NAME_BUFFER_SIZE, "activation%d", layer);
    switch (params->activation){
    case RELU:
        op_desc = TF_NewOperation(tf_model->graph, "Relu", name_buffer);
        break;
    case TANH:
        op_desc = TF_NewOperation(tf_model->graph, "Tanh", name_buffer);
        break;
    case SIGMOID:
        op_desc = TF_NewOperation(tf_model->graph, "Sigmoid", name_buffer);
        break;
    default:
        return DNN_ERROR;
    }
    input.oper = *cur_op;
    TF_AddInput(op_desc, input);
    TF_SetAttrType(op_desc, "T", TF_FLOAT);
    *cur_op = TF_FinishOperation(op_desc, tf_model->status);
    if (TF_GetCode(tf_model->status) != TF_OK){
        return DNN_ERROR;
    }

    return DNN_SUCCESS;
}