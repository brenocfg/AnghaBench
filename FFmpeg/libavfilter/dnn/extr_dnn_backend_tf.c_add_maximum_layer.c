#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {float y; } ;
struct TYPE_11__ {TYPE_1__ val; } ;
struct TYPE_10__ {int /*<<< orphan*/  status; int /*<<< orphan*/  graph; } ;
struct TYPE_9__ {int /*<<< orphan*/ * oper; scalar_t__ index; } ;
typedef  int /*<<< orphan*/  TF_Tensor ;
typedef  TYPE_2__ TF_Output ;
typedef  int /*<<< orphan*/  TF_OperationDescription ;
typedef  int /*<<< orphan*/  TF_Operation ;
typedef  TYPE_3__ TFModel ;
typedef  TYPE_4__ DnnLayerMaximumParams ;
typedef  int /*<<< orphan*/  DNNReturnType ;

/* Variables and functions */
 int /*<<< orphan*/  DNN_ERROR ; 
 int /*<<< orphan*/  DNN_SUCCESS ; 
 int NAME_BUFFER_SIZE ; 
 int /*<<< orphan*/  TF_AddInput (int /*<<< orphan*/ *,TYPE_2__) ; 
 int /*<<< orphan*/ * TF_AllocateTensor (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TF_DataTypeSize (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TF_FLOAT ; 
 int /*<<< orphan*/ * TF_FinishOperation (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ TF_GetCode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * TF_NewOperation (int /*<<< orphan*/ ,char*,char*) ; 
 scalar_t__ TF_OK ; 
 int /*<<< orphan*/  TF_SetAttrTensor (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TF_SetAttrType (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ TF_TensorData (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int const) ; 

__attribute__((used)) static DNNReturnType add_maximum_layer(TFModel *tf_model, TF_Operation **cur_op,
                                       DnnLayerMaximumParams *params, const int layer)
{
    TF_Operation *op;
    TF_Tensor *tensor;
    TF_OperationDescription *op_desc;
    TF_Output input;
    float *y;

    char name_buffer[NAME_BUFFER_SIZE];
    snprintf(name_buffer, NAME_BUFFER_SIZE, "maximum/y%d", layer);

    op_desc = TF_NewOperation(tf_model->graph, "Const", name_buffer);
    TF_SetAttrType(op_desc, "dtype", TF_FLOAT);
    tensor = TF_AllocateTensor(TF_FLOAT, NULL, 0, TF_DataTypeSize(TF_FLOAT));
    y = (float *)TF_TensorData(tensor);
    *y = params->val.y;
    TF_SetAttrTensor(op_desc, "value", tensor, tf_model->status);
    if (TF_GetCode(tf_model->status) != TF_OK){
        return DNN_ERROR;
    }
    op = TF_FinishOperation(op_desc, tf_model->status);
    if (TF_GetCode(tf_model->status) != TF_OK){
        return DNN_ERROR;
    }

    snprintf(name_buffer, NAME_BUFFER_SIZE, "maximum%d", layer);
    op_desc = TF_NewOperation(tf_model->graph, "Maximum", name_buffer);
    input.oper = *cur_op;
    input.index = 0;
    TF_AddInput(op_desc, input);
    input.oper = op;
    TF_AddInput(op_desc, input);
    TF_SetAttrType(op_desc, "T", TF_FLOAT);
    *cur_op = TF_FinishOperation(op_desc, tf_model->status);
    if (TF_GetCode(tf_model->status) != TF_OK){
        return DNN_ERROR;
    }

    return DNN_SUCCESS;
}