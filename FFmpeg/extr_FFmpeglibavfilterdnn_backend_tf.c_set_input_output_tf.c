#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_6__ ;
typedef  struct TYPE_9__   TYPE_5__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int int64_t ;
struct TYPE_10__ {scalar_t__ index; void* oper; } ;
struct TYPE_9__ {scalar_t__ index; void* oper; } ;
struct TYPE_8__ {int height; int width; int channels; float* data; } ;
struct TYPE_7__ {TYPE_2__* output_data; int /*<<< orphan*/  status; TYPE_6__ output; int /*<<< orphan*/ * input_tensor; TYPE_5__ input; scalar_t__ session; int /*<<< orphan*/  graph; } ;
typedef  int /*<<< orphan*/  TF_Tensor ;
typedef  int /*<<< orphan*/  TF_SessionOptions ;
typedef  int /*<<< orphan*/  TF_Operation ;
typedef  TYPE_1__ TFModel ;
typedef  int /*<<< orphan*/  DNNReturnType ;
typedef  TYPE_2__ DNNData ;

/* Variables and functions */
 int /*<<< orphan*/  DNN_ERROR ; 
 int /*<<< orphan*/  DNN_SUCCESS ; 
 int /*<<< orphan*/ * TF_AllocateTensor (int /*<<< orphan*/ ,int*,int,int) ; 
 int /*<<< orphan*/  TF_CloseSession (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TF_DeleteSession (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TF_DeleteSessionOptions (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TF_DeleteTensor (int /*<<< orphan*/ *) ; 
 void* TF_Dim (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  TF_FLOAT ; 
 scalar_t__ TF_GetCode (int /*<<< orphan*/ ) ; 
 void* TF_GraphOperationByName (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ TF_NewSession (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * TF_NewSessionOptions () ; 
 scalar_t__ TF_OK ; 
 int /*<<< orphan*/  TF_SessionRun (scalar_t__,int /*<<< orphan*/ *,TYPE_5__*,int /*<<< orphan*/ **,int,TYPE_6__*,int /*<<< orphan*/ **,int,int /*<<< orphan*/  const**,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ TF_TensorData (int /*<<< orphan*/ *) ; 
 float* av_malloc (int) ; 

__attribute__((used)) static DNNReturnType set_input_output_tf(void *model, DNNData *input, DNNData *output)
{
    TFModel *tf_model = (TFModel *)model;
    int64_t input_dims[] = {1, input->height, input->width, input->channels};
    TF_SessionOptions *sess_opts;
    const TF_Operation *init_op = TF_GraphOperationByName(tf_model->graph, "init");
    TF_Tensor *output_tensor;

    // Input operation should be named 'x'
    tf_model->input.oper = TF_GraphOperationByName(tf_model->graph, "x");
    if (!tf_model->input.oper){
        return DNN_ERROR;
    }
    tf_model->input.index = 0;
    if (tf_model->input_tensor){
        TF_DeleteTensor(tf_model->input_tensor);
    }
    tf_model->input_tensor = TF_AllocateTensor(TF_FLOAT, input_dims, 4,
                                               input_dims[1] * input_dims[2] * input_dims[3] * sizeof(float));
    if (!tf_model->input_tensor){
        return DNN_ERROR;
    }
    input->data = (float *)TF_TensorData(tf_model->input_tensor);

    // Output operation should be named 'y'
    tf_model->output.oper = TF_GraphOperationByName(tf_model->graph, "y");
    if (!tf_model->output.oper){
        return DNN_ERROR;
    }
    tf_model->output.index = 0;

    if (tf_model->session){
        TF_CloseSession(tf_model->session, tf_model->status);
        TF_DeleteSession(tf_model->session, tf_model->status);
    }

    sess_opts = TF_NewSessionOptions();
    tf_model->session = TF_NewSession(tf_model->graph, sess_opts, tf_model->status);
    TF_DeleteSessionOptions(sess_opts);
    if (TF_GetCode(tf_model->status) != TF_OK)
    {
        return DNN_ERROR;
    }

    // Run initialization operation with name "init" if it is present in graph
    if (init_op){
        TF_SessionRun(tf_model->session, NULL,
                      NULL, NULL, 0,
                      NULL, NULL, 0,
                      &init_op, 1, NULL, tf_model->status);
        if (TF_GetCode(tf_model->status) != TF_OK)
        {
            return DNN_ERROR;
        }
    }

    // Execute network to get output height, width and number of channels
    TF_SessionRun(tf_model->session, NULL,
                  &tf_model->input, &tf_model->input_tensor, 1,
                  &tf_model->output, &output_tensor, 1,
                  NULL, 0, NULL, tf_model->status);
    if (TF_GetCode(tf_model->status) != TF_OK){
        return DNN_ERROR;
    }
    else{
        output->height = TF_Dim(output_tensor, 1);
        output->width = TF_Dim(output_tensor, 2);
        output->channels = TF_Dim(output_tensor, 3);
        output->data = av_malloc(output->height * output->width * output->channels * sizeof(float));
        if (!output->data){
            return DNN_ERROR;
        }
        tf_model->output_data = output;
        TF_DeleteTensor(output_tensor);
    }

    return DNN_SUCCESS;
}