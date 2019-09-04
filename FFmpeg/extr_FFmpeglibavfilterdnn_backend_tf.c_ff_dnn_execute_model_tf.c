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
struct TYPE_7__ {scalar_t__ model; } ;
struct TYPE_6__ {TYPE_1__* output_data; int /*<<< orphan*/  status; int /*<<< orphan*/  output; int /*<<< orphan*/  input_tensor; int /*<<< orphan*/  input; int /*<<< orphan*/  session; } ;
struct TYPE_5__ {int height; int width; int channels; int /*<<< orphan*/  data; } ;
typedef  int /*<<< orphan*/  TF_Tensor ;
typedef  TYPE_2__ TFModel ;
typedef  int /*<<< orphan*/  DNNReturnType ;
typedef  TYPE_3__ DNNModel ;

/* Variables and functions */
 int /*<<< orphan*/  DNN_ERROR ; 
 int /*<<< orphan*/  DNN_SUCCESS ; 
 int /*<<< orphan*/  TF_DeleteTensor (int /*<<< orphan*/ *) ; 
 scalar_t__ TF_GetCode (int /*<<< orphan*/ ) ; 
 scalar_t__ TF_OK ; 
 int /*<<< orphan*/  TF_SessionRun (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ **,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TF_TensorData (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

DNNReturnType ff_dnn_execute_model_tf(const DNNModel *model)
{
    TFModel *tf_model = (TFModel *)model->model;
    TF_Tensor *output_tensor;

    TF_SessionRun(tf_model->session, NULL,
                  &tf_model->input, &tf_model->input_tensor, 1,
                  &tf_model->output, &output_tensor, 1,
                  NULL, 0, NULL, tf_model->status);

    if (TF_GetCode(tf_model->status) != TF_OK){
        return DNN_ERROR;
    }
    else{
        memcpy(tf_model->output_data->data, TF_TensorData(output_tensor),
               tf_model->output_data->height * tf_model->output_data->width *
               tf_model->output_data->channels * sizeof(float));
        TF_DeleteTensor(output_tensor);

        return DNN_SUCCESS;
    }
}