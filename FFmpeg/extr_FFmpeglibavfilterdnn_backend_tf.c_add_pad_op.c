#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int int64_t ;
typedef  scalar_t__ int32_t ;
struct TYPE_6__ {int /*<<< orphan*/  status; int /*<<< orphan*/  graph; } ;
struct TYPE_5__ {int /*<<< orphan*/ * oper; scalar_t__ index; } ;
typedef  int /*<<< orphan*/  TF_Tensor ;
typedef  TYPE_1__ TF_Output ;
typedef  int /*<<< orphan*/  TF_OperationDescription ;
typedef  int /*<<< orphan*/  TF_Operation ;
typedef  TYPE_2__ TFModel ;
typedef  int /*<<< orphan*/  DNNReturnType ;

/* Variables and functions */
 int /*<<< orphan*/  DNN_ERROR ; 
 int /*<<< orphan*/  DNN_SUCCESS ; 
 int /*<<< orphan*/  TF_AddInput (int /*<<< orphan*/ *,TYPE_1__) ; 
 int /*<<< orphan*/ * TF_AllocateTensor (int /*<<< orphan*/ ,int*,int,int) ; 
 int /*<<< orphan*/  TF_FLOAT ; 
 int /*<<< orphan*/ * TF_FinishOperation (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ TF_GetCode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TF_INT32 ; 
 int /*<<< orphan*/ * TF_NewOperation (int /*<<< orphan*/ ,char*,char*) ; 
 scalar_t__ TF_OK ; 
 int /*<<< orphan*/  TF_SetAttrString (int /*<<< orphan*/ *,char*,char*,int) ; 
 int /*<<< orphan*/  TF_SetAttrTensor (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TF_SetAttrType (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ TF_TensorData (int /*<<< orphan*/ *) ; 

__attribute__((used)) static DNNReturnType add_pad_op(TFModel *tf_model, TF_Operation **cur_op, const int32_t pad)
{
    TF_Operation *op;
    TF_Tensor *tensor;
    TF_OperationDescription *op_desc;
    TF_Output input;
    int32_t *pads;
    int64_t pads_shape[] = {4, 2};

    input.index = 0;

    op_desc = TF_NewOperation(tf_model->graph, "Const", "pads");
    TF_SetAttrType(op_desc, "dtype", TF_INT32);
    tensor = TF_AllocateTensor(TF_INT32, pads_shape, 2, 4 * 2 * sizeof(int32_t));
    pads = (int32_t *)TF_TensorData(tensor);
    pads[0] = 0;   pads[1] = 0;
    pads[2] = pad; pads[3] = pad;
    pads[4] = pad; pads[5] = pad;
    pads[6] = 0;   pads[7] = 0;
    TF_SetAttrTensor(op_desc, "value", tensor, tf_model->status);
    if (TF_GetCode(tf_model->status) != TF_OK){
        return DNN_ERROR;
    }
    op = TF_FinishOperation(op_desc, tf_model->status);
    if (TF_GetCode(tf_model->status) != TF_OK){
        return DNN_ERROR;
    }

    op_desc = TF_NewOperation(tf_model->graph, "MirrorPad", "mirror_pad");
    input.oper = *cur_op;
    TF_AddInput(op_desc, input);
    input.oper = op;
    TF_AddInput(op_desc, input);
    TF_SetAttrType(op_desc, "T", TF_FLOAT);
    TF_SetAttrType(op_desc, "Tpaddings", TF_INT32);
    TF_SetAttrString(op_desc, "mode", "SYMMETRIC", 9);
    *cur_op = TF_FinishOperation(op_desc, tf_model->status);
    if (TF_GetCode(tf_model->status) != TF_OK){
        return DNN_ERROR;
    }

    return DNN_SUCCESS;
}